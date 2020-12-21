# Question

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

![](8-queens.png)

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

```
Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：暴力法

对于棋盘中的每个格子来说，都有两种情况：

* 放入 Q
* 不放 Q

因此我们可以递归的解决这样的问题，直到将 n 个皇后都放入棋盘中，代码如下：

```java
class Solution {
   public boolean valid(List<Integer> r) {
		int n = r.size();
		int[][] chessboard = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				chessboard[i][j] = 0;
			}
		}
		for (Integer nth : r) {
			int row = nth / n;
			int col = nth % n;
			chessboard[row][col] = 1;
		}
		for (Integer nth : r) {
			if (!validSingle(chessboard, nth, n)) {
				return false;
			}
		}
		return true;
	}

	public boolean validSingle(int[][] chessboard, Integer nth, int n) {

		int row = nth / n;
		int col = nth % n;
		// valid row
		for (int j = 0; j < n; j++) {
			if (j != col && chessboard[row][j] == 1) {
				return false;
			}
		}
		// valid col
		for (int i = 0; i < n; i++) {
			if (i != row && chessboard[i][col] == 1) {
				return false;
			}
		}
		// valid leading diagonal(主对角线)
		for (int i = 1; i < n; i++) {
			int beforeRow = row - i;
			int beforeCol = col - i;
			int nextRow = row + i;
			int nextCol = col + i;
			if (beforeRow >= 0 && beforeRow < n && beforeCol >= 0 && beforeCol < n) {
				if (chessboard[beforeRow][beforeCol] == 1) {
					return false;
				}
				if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n) {
					if (chessboard[nextRow][nextCol] == 1) {
						return false;
					}
				}
			}
		}

		// valid no-leading diagonal(副对角线)
		for (int i = 1; i < n; i++) {
			int beforeRow = row - i;
			int beforeCol = col + i;
			int nextRow = row + i;
			int nextCol = col - i;
			if (beforeRow >= 0 && beforeRow < n && beforeCol >= 0 && beforeCol < n) {
				if (chessboard[beforeRow][beforeCol] == 1) {
					return false;
				}
				if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n) {
					if (chessboard[nextRow][nextCol] == 1) {
						return false;
					}
				}
			}
		}

		return true;

	}

	/**
	 * 递归的解决 N queens 问题
	 * 
	 * @param nth        当前寻找到第 nth 个格子
	 * @param total      总共有多少个格子
	 * @param leftQueens 剩余未放置的皇后个数
	 * @param previous   之前存储的结果，list 中表示之前的皇后存在在第几个格子，以行位优先计算
	 * @param res        存储最终的合法的结果
	 */
	public void solve(int nth, int total, int leftQueens, List<Integer> previous, List<List<String>> res) {
		if (leftQueens == 0) { // 放完了
			if (valid(previous)) { // 如果校验通过
				res.add(genStringRes(previous));
			}
		} else {
			if (nth < total) {
				// 不放皇后
				solve(nth + 1, total, leftQueens, new ArrayList<Integer>(previous), res);
				//
				List<Integer> np = new ArrayList<Integer>(previous);
				np.add(nth);
				solve(nth + 1, total, leftQueens - 1, np, res);
			}
		}
	}

	public List<String> genStringRes(List<Integer> r) {
		List<String> res = new ArrayList<String>();
		int n = r.size();
		char[][] chessboard = new char[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				chessboard[i][j] = '.';
			}
		}
		for (Integer nth : r) {
			int row = nth / n;
			int col = nth % n;
			chessboard[row][col] = 'Q';
		}
		for (int row = 0; row < n; row++) {
			StringBuilder sb = new StringBuilder();
			for (int col = 0; col < n; col++) {
				char c = chessboard[row][col];
				sb.append(c);
			}
			res.add(sb.toString());
		}
		return res;
	}

	public List<List<String>> solveNQueens(int n) {
		List<List<String>> res = new ArrayList<List<String>>();
		solve(0, n*n, n, new ArrayList<Integer>(), res);
		return res;
	}
}
```

算法应该是正确的，但是对于`n x n`的棋盘，从第一个格子开始，每次都会产生2种情况，最后校验是否正确需要花费`O(N^2)`,因此总的时间复杂度位`O(2^(n^2) * n^2)`，当`n=8`时，需要调用`2^64 * 64` 次，在 leetcode 上超时了。

## 解法二：自己写的回溯算法

我们先在棋盘的初始位置放在一个 Queen,然后将该皇后占据的位置在棋盘上标记出来，从剩下未标记的位置开始找剩下皇后的位置，如果没有空余位置但是皇后还有剩余，回溯；或者所有皇后都已放完，保存结果然后回溯。

```c
#include<stdlib.h>
#include<stdio.h>
#include"hashMap.h"
#define MAX_RETURN_SIZE 1024

void printArray(int* arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%d ", *(arr + i));
        }
        else {
            printf("%d, ", *(arr + i));
        }
    }
    printf("]\n");
}

void swap(int* arr, int i, int j) {
    int temp = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = temp;
}

void quickSortR(int* arr, int begin, int end) {
    if (end - begin > 0) {
        int left = begin;
        int right = end;
        int pivot = *(arr + begin);
        while (left < right) {
            while (left < right && *(arr + right) >= pivot) {
                right--;
            }
            while (left < right && *(arr + left) <= pivot) {
                left++;
            }
            swap(arr, left, right);
        }
        swap(arr, left, begin);
        quickSortR(arr, begin, left - 1);
        quickSortR(arr, left + 1, end);
    }
}

void quickSort(int* arr, int size) {
    quickSortR(arr, 0, size - 1);
}

int* copyArray(int* arr, int size) {
    int* newArr = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        *(newArr + i) = *(arr + i);
    }
    return newArr;
}

int isArrayEqual(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (*(arr1 + i) != *(arr2 + i)) {
            return 0;
        }
    }
    return 1;
}

int isRepeat(int** resArray, int size, int* newArray, int n) {
    if (size == 0) {
        return 0;
    }
    else {
        for (int i = 0; i < size; i++) {
            int* arr1 = *(resArray + i);
            if (isArrayEqual(arr1, newArray, n)) {
                return 1;
            }
        }
        return 0;
    }
}

/**
* 是否是合法的 row 和 col,n位棋盘大小
*/
int isLegalRowAndCol(int row, int col, int n) {
    if (row >= 0 && row < n && col >= 0 && col < n) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
* 将棋盘第 row 行和第 col 的位置被皇后占据
*/
void takeUp(char** chessboard, int row, int col, int n) {
    // 占据行和列
    for (int i = 0; i < n; i++) {
        *(*(chessboard + row) + i) = '1';
        *(*(chessboard + i) + col) = '1';
    }
    // 占据两个对角线
    for (int i = 1; i < n; i++) {
        // 主对角线
        int leadingBeforeRow = row - i;
        int leadingBeforCol = col - i;
        int leadingNextRow = row + i;
        int leadingNextCol = col + i;
        // 斜对角线
        int clineBeforeRow = row - i;
        int clineBeforeCol = col + i;
        int clineNextRow = row + i;
        int clineNextCol = col - i;

        if (isLegalRowAndCol(leadingBeforeRow, leadingBeforCol,n)) {
            *(*(chessboard + leadingBeforeRow) + leadingBeforCol) = '1';
        }
        if (isLegalRowAndCol(leadingNextRow, leadingNextCol, n)) {
            *(*(chessboard + leadingNextRow) + leadingNextCol) = '1';
        }
        if (isLegalRowAndCol(clineBeforeRow, clineBeforeCol, n)) {
            *(*(chessboard + clineBeforeRow) + clineBeforeCol) = '1';
        } 
        if (isLegalRowAndCol(clineNextRow, clineNextCol, n)) {
            *(*(chessboard + clineNextRow) + clineNextCol) = '1';
        }
    }
    *(*(chessboard + row) + col) = 'Q';
}

/**
* 放弃某个皇后对棋盘的占据，按照正常的思路，我们需要按照相反的思路去执行，但是这样会有一些重复的判断
* 我们可以换个思路，只需要将这个皇后之前的皇后重新占据即可。
* @param chessboard 一个 nxn 的棋盘，其中用 Q 表示皇后的位置，1 表示已经占据的位置，0表示可以占据的位置
* @param n 棋盘大小
* @param pos 一维数组，表示每个皇后当前所处在棋盘中的位置
* @param currentQueen 当前皇后在 pos 中的 index
*/
void giveUp(char** chessboard, int n, int* pos, int currentQueen) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(chessboard + i) + j) = '0';
        }
    }
    for (int i = 0; i < currentQueen; i++) {
        int p = *(pos + i);
        int row = p / n;
        int col = p % n;
        takeUp(chessboard, row, col, n);
    }
}

/**
* 从当前位置 begin 在棋盘中寻找一个可以放入 Queen 的格子，并返回，如果找不到，返回 -1
*/
int findEnablePosition(char** chessboard, int begin, int n) {
    int i = begin;
    int max = n * n;
    while (i < max) {
        int row = i / n;
        int col = i % n;
        if (*(*(chessboard + row) + col) == '0') {
            return i;
        }
        i++;
    }
    return -1;
}

char** packageRes(int* pos, int n) {
    char** chessboard = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * (n + 1));
        for (int j = 0; j < n; j++) {
            *(row + j) = '.';
        }
        *(row + n) = '\0';
        *(chessboard + i) = row;
    }
    for (int i = 0; i < n; i++) {
        int p = *(pos + i);
        int row = p / n;
        int col = p % n;
        *(*(chessboard + row) + col) = 'Q';
    }
    return chessboard;
}

char* numberToString(int num) {
    char* str = (char*)malloc(sizeof(char) * 1024);
    int size = 0;
    if (num == 0) {
        *(str + size++) = '0';
        *(str + size++) = '\0';
    }
    else {
        while (num > 0) {
            int n = num % 10;
            num = num / 10;
            char c = n + 48;
            *(str + size++) = c;
        }
        *(str + size) = '\0';
        for (int i = 0; i < size / 2; i++) {
            char temp = *(str + i);
            *(str + i) = *(str + size - 1 - i);
            *(str + size - 1 - i) = temp;
        }
    }
    return str;
}

/**
* 将整数数组转换为字符串
*/
char* toString(int* arr, int n) {
    char* str = (char*)malloc(sizeof(char) * 1024);
    int size = 0;
    for (int i = 0; i < n; i++) {
        int num = *(arr + i);
        char* s = numberToString(num);
        char* p = s;
        while (*p != '\0') {
            *(str + size++) = *p++;
        }
        free(s);
    }
    *(str + size) = '\0';
    return str;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** res = (char***)malloc(sizeof(char**) * MAX_RETURN_SIZE);
    // 保存合法的位置，用于去重
    PHashMap hashMap = newHashMap();
    *returnSize = 0;
    /* 
    * 初始化一个 n x n 的棋盘，用于回溯。
    * 当某个格子的值 0 时，表示可以放入Queen，1 表示不能可以放入 Queen, Q 表示该位置已经放入了一个 Queen
    */
    char** chessboard = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * n);
        for (int j = 0; j < n; j++) {
            *(row + j) = '0';
        }
        *(chessboard + i) = row;
    }
    /** 初始一个长度位 n 的数组用来记录每个 Queen 的位置，
    * 从(0,0) ~ (n-1, n-1),以行为优先，依次把格子标记为 0，1,2,3 ... n^2-1
    */
    int* pos = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        *(pos + i) = -1;
    }
    // 从棋盘第一个位置(0,0)开始
    *(*(chessboard + 0) + 0) = 'Q';
    *(pos + 0) = 0;
    // 当前正在寻找第 nth 个皇后
    int nth = 1;
    int loopCounter = 0;
    int repeatCounter = 0;
    takeUp(chessboard, 0, 0, n);
    while (*(pos + 0) < n && nth >=0) {
        loopCounter++;
        if (nth == n) { // 所有的皇后已经找到对应的位置，保存结果
            int* newArray = copyArray(pos, n);
            quickSort(newArray, n);
            char* str = toString(newArray, n);
            if (!hashTableContains(hashMap, str)) {
                *(res + *returnSize) = packageRes(pos, n);
                hashTablePut(hashMap, str, str);
                *returnSize = *returnSize + 1;
            }
            else {
                repeatCounter++;
            }
            // 继续回溯
            nth--;
            giveUp(chessboard, n, pos, nth);
        }
        else {
            int currentPos = *(pos + nth);
            int p = findEnablePosition(chessboard, currentPos + 1, n);
            if (p != -1) { // 找到一个合适的位置,继续找下一个
                int row = p / n;
                int col = p % n;
                *(pos + nth) = p;
                takeUp(chessboard, row, col, n);
                nth++;
            }
            else { // 没找到合适的位置，回溯
                *(pos + nth) = -1;
                nth--;
                giveUp(chessboard, n, pos, nth);
            }
        }
        
    }
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        *(*returnColumnSizes + i) = n;
    }
    destoryHashMap(hashMap);
    printf("loopCounter:%d,repeatCounter:%d\n", loopCounter, repeatCounter);
    return res;

}

void printRes(char*** res, int row, int* cols) {
    printf("[\n");
    for (int i = 0; i < row; i++) {
        char** chessBoard = *(res + i);
        int col = *(cols + i);
        printf("\t[\n");
        for (int j = 0; j < col; j++) {
            printf("\t\t[ %s ]\n", *(chessBoard + j));
        }
        printf("\t]\n");
    }
    printf("]\n");
}

void testHashMap() {
    int size = 1000;
    PHashMap map = newHashMap();
    for (int i = 0; i < size; i++) {
        char* str = numberToString(i);
        hashTablePut(map, str, str);
    }
    for (int i = 0; i < size; i++) {
        char* str = numberToString(i);
        int r = hashTableContains(map, str);
        if (r == 0) {
            printf("hashMap not contains key:%s\n", str);
        }
        free(str);
    }
}

int main() {
    int n = 8;
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    char*** res = solveNQueens(n, &returnSize, &returnColumnSizes);
    printf("returnSize:%d\n", returnSize);
    printRes(res, returnSize, returnColumnSizes);
	system("pause");
	return 0;
}
```

为了去重，借助了我自己写的 `HashMap`

```c
#pragma once
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"RBTree.h"
#include"LinkList.h"
#define LINK_LIST_WAY 0
#define RB_TREE_WAY 1
#define N 1024
#define LINK_LIST_MAX 10

typedef struct HashTable {
	int way; // 0-链表 1-红黑树
	PLinkList list;
	PRBTree tree;
	int size;
} HashTable, * PHashTable;

typedef struct HashMap {
	int size;
	PHashTable* tables;
}HashMap, * PHashMap;

PHashTable newHashTable() {
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	PRBTree tree = newRBTree();
	PLinkList list = newLinkList();
	hashTable->list = list;
	hashTable->tree = tree;
	hashTable->size = 0;
}

PHashMap newHashMap() {
	PHashMap hashMap = (PHashMap)malloc(sizeof(HashMap));
	PHashTable* tables = (PHashTable*)malloc(sizeof(PHashTable) * N);
	for (int i = 0; i < N; i++) {
		*(tables + i) = NULL;
	}
	hashMap->size = 0;
	hashMap->tables = tables;
	return hashMap;
}

int hashCode(char* key) {
	int sum = 0;
	while (*key != '\0') {
		sum = sum * 2 + *key - 48;
		key++;
	}
	return sum;
}

void linkListToRBTree(PHashTable table) {
	PLinkList list = table->list;
	PLinkListNode  root = list->root;
	while (root != list->nil) {
		PLinkListNode temp = root;
		root = root->next;
		PRBTreeNode node = newRBTreeNode(table->tree, temp->key, temp->value);
		RBInsert(table->tree, node);
		free(temp);
	}
	table->list->root = table->list->nil;
	table->way = RB_TREE_WAY;
}


void hashTablePut(PHashMap map, char* key, char* value) {
	int code = hashCode(key);
	int pos = code % N;
	PHashTable table = *(map->tables + pos);
	if (table == NULL) {
		PHashTable table = newHashTable();
		table->way = LINK_LIST_WAY;
		PLinkListNode node = newLinkListNode(table->list, key, value);
		linkListPut(table->list, node);
		table->size = 1;
		*(map->tables + pos) = table;
	}
	else {
		if (table->way == RB_TREE_WAY) {
			PRBTreeNode node = newRBTreeNode(table->tree, key, value);
			RBInsert(table->tree, node);
			table->size = table->size + 1;
		}
		else {
			if (table->size + 1 > LINK_LIST_MAX) {
				linkListToRBTree(table);
				PRBTreeNode node = newRBTreeNode(table->tree, key, value);
				RBInsert(table->tree, node);
				table->size = table->size + 1;
			}
			else {
				PLinkListNode node = newLinkListNode(table->list, key, value);
				linkListPut(table->list, node);
				table->size = table->size + 1;
			}
		}
	}
}

char* hashTableGetOrElse(PHashMap map, char* key, char* defaultV) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table->way == LINK_LIST_WAY) {
		PLinkListNode node = linkListGet(table->list, key);
		if (node != table->list->nil) {
			return node->value;
		}
		else {
			return defaultV;
		}

	}
	else {
		PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
		if (node != table->tree->nil) {
			return node->value;
		}
		else {
			return defaultV;
		}
	}
}

int hashTableContains(PHashMap map, char* key) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table == NULL) {
		return 0;
	}
	else {
		if (table->way == LINK_LIST_WAY) {
			PLinkListNode node = linkListGet(table->list, key);
			if (node != table->list->nil) {
				return 1;
			}
			else {
				return 0;
			}

		}
		else {
			PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
			if (node != table->tree->nil) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	
}

void hashTableRemove(PHashMap map, char* key) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table->way == LINK_LIST_WAY) {
		linkListRemove(table->list, key);
	}
	else {
		PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
		if (node != table->tree->nil) {
			RBRemove(table->tree, node);
		}
	}
}

void destoryHashMap(PHashMap map) {
	PHashTable* tables = map->tables;
	for (int i = 0; i < N; i++) {
		PHashTable table = *(tables + i);
		if (table != NULL) {
			destoryLinkList(table->list);
			destoryRBTree(table->tree);
			free(table);
		}
	}
	free(tables);
	free(map);
}
```

冲突较少时，使用链表：

```c
#pragma once
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
// 链表节点
typedef struct LinkListNode {
	char* key;
	char* value;
	struct LinkListNode* next;
} LinkListNode, * PLinkListNode;

typedef struct LinkList {
	PLinkListNode root;
	PLinkListNode nil;
}LinkList, * PLinkList;

PLinkList newLinkList() {
	PLinkList list = (PLinkList)malloc(sizeof(LinkList));
	PLinkListNode nil = (PLinkListNode)malloc(sizeof(LinkListNode));
	nil->key = '\0';
	nil->value = 0;
	nil->next = nil;
	list->nil = nil;
	list->root = nil;
	return list;
}

PLinkListNode newLinkListNode(PLinkList list, char* key, char* value) {
	PLinkListNode node = (PLinkListNode)malloc(sizeof(LinkListNode));
	node->key = key;
	node->value = value;
	node->next = list->nil;
	return node;
}

void linkListPut(PLinkList list, PLinkListNode node) {
	if (list->root == NULL) {
		list->root = node;
		node->next = list->nil;
	}
	else {
		node->next = list->root;
		list->root = node;
	}
}

PLinkListNode linkListGet(PLinkList list, char* key) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		if (strcmp(root->key, key) == 0) {
			return root;
		}
		root = root->next;
	}
	return list->nil;
}

void linkListRemove(PLinkList list, char* key) {
	PLinkListNode root = list->root;
	PLinkListNode previous = list->nil;
	while (root != list->nil) {
		if (strcmp(root->key, key) != 0) {
			previous = root;
			root = root->next;
		}
		else {
			if (previous == list->nil) { // remove root
				list->root = root->next;
				free(root);
				return;
			}
			else {
				previous->next = root->next;
				free(root);
				return;
			}
		}
	}
}

void destoryLinkList(PLinkList list) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		PLinkListNode temp = root;
		root = root->next;
		free(temp);
	}
	free(list->nil);
	free(list);
}

void printLinkList(PLinkList list) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		printf("%s->", root->key);
		root = root->next;
	}
	printf("null\n");
}
```

冲突较多时使用红黑树：

```c
#pragma once
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<string.h>
#define BLACK 0
#define RED 1


// 红黑树的节点定义
typedef struct RBTreeNode {
	char* key; // 元素的key
	char* value;
	int color; // 节点的颜色 0-黑色 1-红色
	struct RBTreeNode* parent; // 父节点指针
	struct RBTreeNode* left; // 左子树指针
	struct RBTreeNode* right; // 右子树指针
}RBTreeNode, * PRBTreeNode;

// 红黑树构建定义
typedef struct RBTree {
	PRBTreeNode root; // 根节点
	PRBTreeNode nil; // 哨兵节点 nil,表示所有空的子节点
}RBTree, * PRBTree;

// 存放红黑树节点的链表
typedef struct RBTreeNodeList {
	PRBTreeNode node;
	struct RBTreeNodeList* next;
}RBTreeNodeList, * PRBTreeNodeList;

// 初始化一棵红黑树，根节点为 NULL
PRBTree newRBTree() {
	PRBTree tree = (PRBTree)malloc(sizeof(RBTree));
	PRBTreeNode nil = (PRBTreeNode)malloc(sizeof(RBTreeNode));
	// nil 的颜色为黑色，其余都无所谓
	char* key = (char*)malloc(sizeof(char) * 1);
	*key = '\0';
	nil->key = key;
	nil->value = key;
	nil->color = BLACK;
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	tree->root = nil;
	tree->nil = nil;
	return tree;
}

PRBTreeNode newRBTreeNode(PRBTree tree, char* key, char* value) {
	PRBTreeNode node = (PRBTreeNode)malloc(sizeof(RBTreeNode));
	node->key = key;
	node->value = value;
	node->color = RED;
	node->left = tree->nil;
	node->right = tree->nil;
	node->parent = tree->nil;
	return node;
}

/**
* 红黑树的高度
*/
int getRBTreeHeight(PRBTree tree, PRBTreeNode root) {
	if (root == tree->nil) {
		return 0;
	}
	else {
		int lh = getRBTreeHeight(tree, root->left);
		int rh = getRBTreeHeight(tree, root->right);
		return max(lh, rh) + 1;
	}
}

PRBTreeNode RBMin(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		if (root->left != tree->nil) {
			RBMin(tree, root->left);
		}
		else {
			return root;
		}
	}
	else {
		return tree->nil;
	}
}

PRBTreeNode RBGetByKey(PRBTree tree, PRBTreeNode root, char* key) {
	if (root == tree->nil) {
		return tree->nil; // not found
	}
	else if (strcmp(root->key, key) == 0) {
		return root;
	}
	else if (strcmp(root->key, key) < 0) {
		return RBGetByKey(tree, root->right, key);
	}
	else {
		return RBGetByKey(tree, root->left, key);
	}
}
/**
* 对红黑树 tree 中的 x 进行 left 旋转
*/
void leftRotate(PRBTree tree, PRBTreeNode x) {
	PRBTreeNode y = x->right;
	x->right = y->left;
	if (y->left != tree->nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == tree->nil) {
		tree->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

/**
* 对红黑树 tree 中的 y 进行 right 旋转
*/
void rightRotate(PRBTree tree, PRBTreeNode y) {
	PRBTreeNode x = y->left;
	y->left = x->right;
	if (x->right != tree->nil) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == tree->nil) {
		tree->root = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}

/**
* 对 z 节点进行插入修复
*/
void RBInsertFixup(PRBTree tree, PRBTreeNode z) {
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			PRBTreeNode y = z->parent->parent->right;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				continue;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftRotate(tree, z);
					continue;
				}
				else {
					if (z->parent != tree->nil) {
						z->parent->color = BLACK;
					}
					if (z->parent->parent != tree->nil) {
						z->parent->parent->color = RED;
						rightRotate(tree, z->parent->parent);
					}
				}
			}


		}
		else {
			PRBTreeNode y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				continue;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(tree, z);
					continue;
				}
				else {
					if (z->parent != tree->nil) {
						z->parent->color = BLACK;
					}
					if (z->parent->parent != tree->nil) {
						z->parent->parent->color = RED;
						leftRotate(tree, z->parent->parent);
					}
				}
			}
		}
	}
	tree->root->color = BLACK;
}

void RBInsert(PRBTree tree, PRBTreeNode z) {
	PRBTreeNode y = tree->nil;
	PRBTreeNode x = tree->root;
	while (x != tree->nil) {
		y = x;
		if (strcmp(z->key, x->key) < 0) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (y == tree->nil) {
		tree->root = z;
	}
	else if (strcmp(z->key, y->key) < 0) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	z->left = tree->nil;
	z->right = tree->nil;
	z->color = RED;
	RBInsertFixup(tree, z);
}

/**
* 对节点 x 进行删除修复
*/
void RBRemoveFixup(PRBTree tree, PRBTreeNode x) {
	while (x != tree->nil && x != tree->root && x->color == BLACK) {
		if (x == x->parent->left) {
			PRBTreeNode w = x->parent->right;
			if (w->color == RED && w != tree->nil) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(tree, x->parent);
				w = x->parent->right;
			}
			if (w == tree->nil
				|| (w != tree->nil && (w->left == tree->nil || w->left->color == BLACK)
					&& (w->right == tree->nil || w->right->color == BLACK))) {
				if (w != tree->nil) {
					w->color = RED;
				}
				x = x->parent;
				continue;
			}
			else if (w->right == tree->nil || w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(tree, w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->right->color = BLACK;
			leftRotate(tree, x->parent);
			x = tree->root;
		}
		else {
			PRBTreeNode w = x->parent->left;
			if (w != tree->nil && w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(tree, x->parent);
				w = x->parent->left;
			}
			if (w == tree->nil
				|| (w != tree->nil && (w->left == tree->nil || w->left->color == BLACK)
					&& (w->right == tree->nil || w->right->color == BLACK))) {
				if (w != tree->nil) {
					w->color = RED;
				}
				x = x->parent;
				continue;
			}
			else if (w->left == tree->nil || w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				leftRotate(tree, w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left->color = BLACK;
			rightRotate(tree, x->parent);
			x = tree->root;
		}
	}
	x->color = BLACK;
}

void RBTransplant(PRBTree tree, PRBTreeNode u, PRBTreeNode v) {
	if (u->parent == tree->nil) {
		tree->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if (v != tree->nil) {
		v->parent = u->parent;
	}
}

void RBRemove(PRBTree tree, PRBTreeNode z) {
	PRBTreeNode y = z;
	PRBTreeNode x = tree->root;
	int yOriginalColor = y->color;
	if (z->left == tree->nil) {
		x = z->right;
		RBTransplant(tree, z, z->right);
	}
	else if (z->right == tree->nil) {
		x = z->left;
		RBTransplant(tree, z, z->left);
	}
	else {
		y = RBMin(tree, z->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			RBTransplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTransplant(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (yOriginalColor == BLACK) {
		RBRemoveFixup(tree, x);
	}
	free(z);
}

void destoryRBTree(PRBTree tree) {
	while (tree->root != tree->nil) {
		RBRemove(tree, tree->root);
	}
	free(tree->nil);
	free(tree);
}

/**
* 红黑树的中序遍历
*/
void RBTreeMiddleTraverse(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		RBTreeMiddleTraverse(tree, root->left);
		if (root->color == RED) {
			printf("红 ");
		}
		else {
			printf("黑 ");
		}
		printf("%s ", root->key);
		RBTreeMiddleTraverse(tree, root->right);
	}
}

/**
* 打印指定层数的数
* @param root 根节点
* @param currentLevel 当前层
* @param level 需要打印的层数节点
*/
void printLevel(PRBTree tree, PRBTreeNode root, int currentLevel, int level, int space) {
	if (root != tree->nil) {
		if (currentLevel == level) { // 到达对应的层数
			if (root->color == RED) {
				printf("R");
			}
			else {
				printf("B");
			}
			printf("%s", root->key);
			for (int i = 0; i < space; i++) {
				printf(" ");
			}
		}
		else { // 还没到,继续往下找
			printLevel(tree, root->left, currentLevel + 1, level, space);
			printLevel(tree, root->right, currentLevel + 1, level, space);
		}
	}
	else {
		printf("B-");
		for (int i = 0; i < space; i++) {
			printf(" ");
		}
	}
}

/**
* 层序遍历，更直观的看出树的形状
*/
void levelTraverse(PRBTree tree) {
	int height = getRBTreeHeight(tree, tree->root);
	int d = 2;
	for (int i = 0; i < height; i++) {
		int step = pow(2, height - 1 - i) * 2;
		for (int j = 0; j < step; j++) {
			printf(" ");
		}
		int dis = pow(2, height - i) - 1;
		printLevel(tree, tree->root, 0, i, dis * d);
		printf("\n\n");
	}
}


/**
* 校验规则1和3，
* 1.对于红黑树来说，每个节点，要么是红色，要么是黑色
* 3. 叶节点 nil 是黑色的
*/
int validRule1And3(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		int r = 0;
		if (root->color == RED || root->color == BLACK) {
			r = 1;
		}
		else {
			printf("node key is: %s, valid rule 1 failure\n", root->key);
		}
		int rLeft = validRule1And3(tree, root->left);
		int rRight = validRule1And3(tree, root->right);
		return r && rLeft && rRight;
	}
	else {
		if (root->color == BLACK) {
			return 1;
		}
		else {
			printf("leaf node nil is not black\n");
			return 0;
		}
	}
}

/**
* 校验规则4：如果一个节点是红色的，那么他的两个字点都是黑色的
*/
int validRule4(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		if (root->color == BLACK) {
			return validRule4(tree, root->left) && validRule4(tree, root->right);
		}
		else {
			int r = 0;
			if (root->left->color == BLACK && root->right->color == BLACK) {
				r = 1;
			}
			else {
				printf("node %d is red, but its left and right not all black\n", root->key);
			}
			return r && validRule4(tree, root->left) && validRule4(tree, root->right);
		}
	}
	else { // nil 不需要校验，直接返回成功
		return 1;
	}
}


/**
* 计算红黑树所有的叶子节点，将其保存在 list 中
*/
void getAllLeafNodesR(PRBTree tree, PRBTreeNode root, PRBTreeNodeList* list) {

	if (root != tree->nil) {
		// 根节点不为空，且左右子树都为空时，为叶节点
		if (root->left == tree->nil && root->right == tree->nil) {
			if (*list == NULL) {
				*list = (PRBTreeNodeList)malloc(sizeof(RBTreeNodeList));
				(*list)->node = root;
				(*list)->next = NULL;
			}
			else {
				PRBTreeNodeList newNode = (PRBTreeNodeList)malloc(sizeof(RBTreeNodeList));
				newNode->node = root;
				newNode->next = *list;
				*list = newNode;
			}
		}
		else {
			getAllLeafNodesR(tree, root->left, list);
			getAllLeafNodesR(tree, root->right, list);
		}
	}
}

/**
* 获取红黑树所有的叶子节点，使用链表的形式返回
*/
PRBTreeNodeList getAllLeafNodes(PRBTree tree, PRBTreeNode root) {
	PRBTreeNodeList list = NULL;
	getAllLeafNodesR(tree, root, &list);
	return list;
}

/**
* 从节点 root 到达 节点 target 需要经历的黑色节点数
* 如果从节点 root 无法通过左子树或右子树到达 target, 返回 -1，表示不可达
*/
int clcReachLeavesBlackNodes(PRBTree tree, PRBTreeNode root, PRBTreeNode target, int blackNodes) {
	if (root != tree->nil) {
		int currentBlackNodes = 0;
		if (root->color == BLACK) {
			currentBlackNodes = 1;
		}
		if (strcmp(target->key, root->key) < 0) {
			return clcReachLeavesBlackNodes(tree, root->left, target, blackNodes + currentBlackNodes);
		}
		else if (strcmp(target->key, root->key) > 0) {
			return clcReachLeavesBlackNodes(tree, root->right, target, blackNodes + currentBlackNodes);
		}
		else { // 找到了
			return  blackNodes + currentBlackNodes;
		}
	}
	else { // 没找到
		return -1;
	}
}

/**
* 校验根节点到所有叶子节点经过的黑色节点数，比较是否相等，如果都相等，返回1，否则返回0
* 对于不可达的节点，使用 -1 表示，不需要校验
*/
int validRootReachEachLeaves(PRBTree tree, PRBTreeNode root, PRBTreeNodeList leaves, int leavesSize) {
	int* res = (int*)malloc(sizeof(int) * leavesSize);
	PRBTreeNodeList p = leaves;
	int previous = -1;
	while (p != NULL) {
		int blackNodes = clcReachLeavesBlackNodes(tree, root, p->node, 0);
		if (blackNodes != -1) {
			if (previous == -1) { // 第一次遇到可达的叶子节点
				previous = blackNodes;
			}
			else {
				if (blackNodes != previous) {
					printf("root key:%s reach leaf key:%s is not equal previous\n", root->key, p->node->key);
					return 0;
				}
			}
		}
		p = p->next;
	}
	return 1;
}

/**
* 计算红黑树所有的非叶子节点到所有叶子节点的简单路径的黑色根节点数量
*/
void validRule5R(PRBTree tree, PRBTreeNode root, PRBTreeNodeList leaves, int leavesSize, int* returnR5) {
	if (root != tree->nil) {
		int r = validRootReachEachLeaves(tree, root, leaves, leavesSize);
		if (r == 0) {
			*returnR5 = 0;
		}
		validRule5R(tree, root->left, leaves, leavesSize, returnR5);
		validRule5R(tree, root->right, leaves, leavesSize, returnR5);
	}
}

/**
* 校验规则 5：对每个节点，到其所有后代的叶节点的简单路径上，均包含相同数目的黑色节点
* @return 该节点到左右子树的黑色节点数
*/
int validRule5(PRBTree tree, PRBTreeNode root) {
	PRBTreeNodeList leaves = getAllLeafNodes(tree, root);
	PRBTreeNodeList p = leaves;
	int leavesSize = 0;
	while (p != NULL) {
		leavesSize++;
		p = p->next;
	}
	int returnR5 = 1;
	validRule5R(tree, root, leaves, leavesSize, &returnR5);
	p = leaves;
	while (p != NULL) {
		PRBTreeNodeList q = p;
		p = p->next;
		free(q);
	}
	return returnR5;
}

/**
* 校验一棵红黑树是否符合以下红黑树的规则
* 1. 每个节点，要么是红色，要么是黑色
* 2. 根节点是黑色的
* 3. 每个叶节点 nil 是黑色的
* 4. 如果一个节点是红色的，那么他的两个字点都是黑色的
* 5. 对每个节点，到其所有后代的叶节点的简单路径上，均包含相同数目的黑色节点
*/
int valid(PRBTree tree) {
	int r13 = validRule1And3(tree, tree->root);
	int r2 = 0;
	if (tree->root->color == BLACK) {
		r2 = 1;
	}
	else {
		printf("root node is not black\n");
		r2 = 0;
	}
	int r4 = validRule4(tree, tree->root);
	int r5 = validRule5(tree, tree->root);
	return r13 && r2 && r4 & r5;;
}
```

然后计算当n=8时，还是超时了，但是可以算出结果的，需要十几秒的时间，比暴力法靠谱的。看来是时候看一下官方题解了。



## 解法三：官方题解的回溯法

在n皇后的问题中，有一个定理：如果要放n个皇后的充要条件是每行每列有且只有一个皇后。当放置一个皇后时，我们不需要找所有的可以放置的点。如果下一行可以放置皇后，继续。否则直接回溯。代码如下：

```c
#include<stdlib.h>
#include<stdio.h>
#define MAX_RETURN_SIZE 1024

/**
* 是否是合法的 row 和 col,n位棋盘大小
*/
int isLegalRowAndCol(int row, int col, int n) {
    if (row >= 0 && row < n && col >= 0 && col < n) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
* 将棋盘第 row 行和第 col 的位置被皇后占据
*/
void takeUp(char** chessboard, int row, int col, int n) {
    // 占据行和列
    for (int i = 0; i < n; i++) {
        *(*(chessboard + row) + i) = '1';
        *(*(chessboard + i) + col) = '1';
    }
    // 占据两个对角线
    for (int i = 1; i < n; i++) {
        // 主对角线
        int leadingBeforeRow = row - i;
        int leadingBeforCol = col - i;
        int leadingNextRow = row + i;
        int leadingNextCol = col + i;
        // 斜对角线
        int clineBeforeRow = row - i;
        int clineBeforeCol = col + i;
        int clineNextRow = row + i;
        int clineNextCol = col - i;

        if (isLegalRowAndCol(leadingBeforeRow, leadingBeforCol, n)) {
            *(*(chessboard + leadingBeforeRow) + leadingBeforCol) = '1';
        }
        if (isLegalRowAndCol(leadingNextRow, leadingNextCol, n)) {
            *(*(chessboard + leadingNextRow) + leadingNextCol) = '1';
        }
        if (isLegalRowAndCol(clineBeforeRow, clineBeforeCol, n)) {
            *(*(chessboard + clineBeforeRow) + clineBeforeCol) = '1';
        }
        if (isLegalRowAndCol(clineNextRow, clineNextCol, n)) {
            *(*(chessboard + clineNextRow) + clineNextCol) = '1';
        }
    }
    *(*(chessboard + row) + col) = 'Q';
}

/**
* 放弃某个皇后对棋盘的占据，按照正常的思路，我们需要按照相反的思路去执行，但是这样会有一些重复的判断
* 我们可以换个思路，只需要将这个皇后之前的皇后重新占据即可。
* @param chessboard 一个 nxn 的棋盘，其中用 Q 表示皇后的位置，1 表示已经占据的位置，0表示可以占据的位置
* @param n 棋盘大小
* @param pos 一维数组，表示每个皇后当前所处在棋盘中的位置
* @param currentQueen 当前皇后在 pos 中的 index
*/
void giveUp(char** chessboard, int n, int* pos, int currentQueen) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(chessboard + i) + j) = '0';
        }
    }
    for (int i = 0; i < currentQueen; i++) {
        int p = *(pos + i);
        int row = p / n;
        int col = p % n;
        takeUp(chessboard, row, col, n);
    }
}
/**
* 将棋盘的结果保存起来
*/
void putToResult(char** chessboard, int n, char ***res, int* returnSize) {
    char** r = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * (n + 1));
        for (int j = 0; j < n; j++) {
            char c = *(*(chessboard + i) + j);
            if (c == 'Q') {
                *(row + j) = 'Q';
            }
            else {
                *(row + j) = '.';
            }
        }
        *(row + n) = '\0';
        *(r + i) = row;
    }
    *(res + *returnSize) = r;
    *returnSize = *returnSize + 1;
}

/**
* 回溯法解决八皇后问题
* @param chessboard 一个 nxn的棋盘，Q 表示皇后，1表示已经被占领的位置 0 表示可以占领的位置
* @param row 当前需要在 row 行放置元素
* @param res 保存结果的集合
* @param returnSize 最终结果集的 size
* @param pos 存储每次皇后放置的位置，从0~n^2-1,以行优先计算
*/
void solve(char** chessboard, int row, int n, char ***res, int *returnSize, int *pos) {
    for (int col = 0; col < n; col++) {
        if (*(*(chessboard + row) + col) == '0') {// 如果找打合适的位置就占领之
            takeUp(chessboard, row, col, n);
            int p = row * n + col;
            *(pos + row) = p;  // 记录位置
            if (row + 1 == n) { // 如果已经把所有的皇后都填入，保存结果，否则继续尝试往下一行放置皇后
                putToResult(chessboard, n, res, returnSize);
            }
            else
            {
                solve(chessboard, row + 1, n, res, returnSize, pos);
            }
            //无论是找到一个解还是下一行无法找到合适的位置，我们都进行回溯
            giveUp(chessboard, n, pos, row);
        }
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** res = (char***)malloc(sizeof(char**) * MAX_RETURN_SIZE);
    // 保存合法的位置，用于去重
    *returnSize = 0;
    /*
    * 初始化一个 n x n 的棋盘，用于回溯。
    * 当某个格子的值 0 时，表示可以放入Queen，1 表示不能可以放入 Queen, Q 表示该位置已经放入了一个 Queen
    */
    char** chessboard = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * (n+1));
        for (int j = 0; j < n; j++) {
            *(row + j) = '0';
        }
        *(row + n) = '\0';
        *(chessboard + i) = row;
    }
    int* pos = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        *(pos + i) = -1;
    }
    solve(chessboard, 0, n, res, returnSize, pos);
    *returnColumnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        *(*returnColumnSizes + i) = n;
    }
    return res;
}

void printRes(char*** res, int row, int* cols) {
    printf("[\n");
    for (int i = 0; i < row; i++) {
        char** chessBoard = *(res + i);
        int col = *(cols + i);
        printf("\t[\n");
        for (int j = 0; j < col; j++) {
            printf("\t\t[ %s ]\n", *(chessBoard + j));
        }
        printf("\t]\n");
    }
    printf("]\n");
}


int main() {
    int n = 12;
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    char*** res = solveNQueens(n, &returnSize, &returnColumnSizes);
    printf("returnSize:%d\n", returnSize);
    // printRes(res, returnSize, returnColumnSizes);
	system("pause");
	return 0;
}
```

