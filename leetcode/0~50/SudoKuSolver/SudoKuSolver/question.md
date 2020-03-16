# Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

* Each of the digits 1-9 must occur exactly once in each row.
* Each of the digits 1-9 must occur exactly once in each column.
* Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

Empty cells are indicated by the character '.'.

![](250px-Sudoku-by-L2G-20050714.svg (1).png)

A sudoku puzzle...

![](250px-Sudoku-by-L2G-20050714_solution.svg.png)


...and its solution numbers marked in red.

Note:

The given board contain only digits 1-9 and the character '.'.
You may assume that the given Sudoku puzzle will have a single unique solution.
The given board size is always 9x9.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

没有什么好的方法，只能使用回溯法了。我们准备三个`9x10`的二维数组`rows[9] [10],cols[9] [10],subBoxes[9] [10]`。

* `rows[i] [j]`表示第`i`行，数字`j`出现了多少次
* `cols[i][j]` 表示第`i`列，数字`j`出现了多少次
* `subBoxes[i][j]` 表示第`i`个 sub box， 数字`j`出现了多少次

因此，对于任意的方格元素`board[i][j]` 我们知道他属于第`i`行，第`j`列，第`i/3*3+j/3`个 sub box.

我们从`[0] [0]`开始，按照行优先，依次遍历 `board`，如果`borad[i][j]`已经存在数字，说明该数字已经存在或者已经计算出，我们接着寻找下一个，如果`board[i][j] == '.'`,说明该位置还未填入数字，我们需要计算，我们让`k = 1 to 9`,如果`board[i][j]=k`使得`row[i][k]=1 && cols[j][k]=1 && subBox[i/3*3+j/3][k]=1`说明 k 合法，否则我们继续让 `k` 自增，直到满足要求。

但是随着不断的往下遍历，我们会出现一些例外的情况，如`k = 1 to 9`对于`board[i][j]`来说都不能满足，此时我们需要回溯。那么如何进行回溯呢？这里我们使用贪心算法，每次回溯到距离当前宫格最近的可回溯点。

对于题目已经给出的数字是不能进行回溯的，因此我们还需要一个标记数组`tag[9][9]`,来表示`tag[i][j]`是否可以进行回溯，不能回溯就继续让 `k`自增。

当我们找到确定的回溯方格`borad[m][n]`时，我们让`k = board[m][n] + 1 to 9`  然后按照上面的思路继续执行。

代码如下：

```c
#include<stdlib.h>
#include<stdio.h>


/**
* 根据给定的 board,对上面的数组进行初始化
* @param board 原数组
* @param boardSize boardSize
* @param boardColSize 每行元素个数
* @param rows 表示第`i`行，数字`j`出现了多少次
* @param cols 表示第`i`列，数字`j`出现了多少次
* @param subBox 表示第`i`个 sub box， 数字`j`出现了多少次
* @param tag 表示 board[i][j]个 元素是否可以回溯 0-不可用 1-可以
*/
void initArray(
	char** board, 
	int boardSize, 
	int* boardColSize, 
	int rows[][10], 
	int cols[][10],
	int subBox[][10],
	int tag[][9]) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < *(boardColSize + i); j++) {
			char c = *(*(board + i) + j);
			if (c == '.') {
				tag[i][j] = 1;
			}
			else {
				int number = c - 48;
				rows[i][number] = 1;
				cols[j][number] = 1;
				int subBoxIndex = i / 3 * 3 + j / 3;
				subBox[subBoxIndex][number] = 1;
				tag[i][j] = 0;
			}
		}
	}
}

/**
* 从 1~9 中找打合适的k 填入第i行，第j列的方格中，如果找不到，找出最近的回溯点
* @param board 原数独数组
* @param nth 第 nth 方格
* @param i 第 i 行
* @param j 第 j 列
* @param subBoxesIndex 子方格的角标
* @param kInitValue k 的初始值
* @param m 回溯到第 m 行的指针
* @param n 回溯到第 n 列的指针
* @param minReCallNth 回溯到第 minReCallNth 方格的指针
* @param rows 表示第`i`行，数字`j`出现了多少次
* @param cols 表示第`i`列，数字`j`出现了多少次
* @param subBox 表示第`i`个 sub box， 数字`j`出现了多少次
* @param tag 表示 board[i][j]个 元素是否可以回溯 0-不可用 1-可以
*/
void findK(
	char** board, 
	int nth, 
	int i, 
	int j, 
	int subBoxIndex,
	int kInitValue,
	int *m,
	int *n,
	int * minReCallNth,
	int rows[][10],
	int cols[][10],
	int subBox[][10],
	int tag[][9]
) {
	int isFind = 0;
	for (int k = kInitValue; k <= 9; k++) {
		// 符合条件
		if (rows[i][k] == 0 && cols[j][k] == 0
			&& subBox[subBoxIndex][k] == 0) {
			char number = k + 48;
			*(*(board + i) + j) = number;
			rows[i][k] = 1;
			cols[j][k] = 1;
			subBox[subBoxIndex][k] = 1;
			isFind = 1;
			// 找到符合的，就将之前的不符合的清空
			break;
		}		
	}

	if (isFind == 1) {
		*m = -1;
		*n = -1;
		*minReCallNth = INT_MAX;
	}
	else {
		// 查找最近一个可回溯点，然后回溯
		for (int counter = nth - 1; counter >= 0; counter--) {
			int x = counter / 9;
			int y = counter % 9;
			if (tag[x][y] == 1) { // 可回溯
				*m = x;
				*n = y;
				*minReCallNth = counter;
				break;
			}
		}
	}
}


/**
* 根据给定的 board,对上面的数组进行初始化
* @param board 原数组
* @param boardSize boardSize
* @param boardColSize 每行元素个数
* @param nth 以行为优先遍历，从 0 开始，到 80 结束，表示计算到第 nth 个宫格
* @param rows 表示第`i`行，数字`j`出现了多少次
* @param cols 表示第`i`列，数字`j`出现了多少次
* @param subBox 表示第`i`个 sub box， 数字`j`出现了多少次
* @param tag 表示 board[i][j]个 元素是否可以回溯 0-不可用 1-可以
*/
void solve(
	char** board, 
	int boardSize, 
	int* boardColSize, 
	int nth,
	int rows[][10],
	int cols[][10],
	int subBox[][10],
	int tag[][9]
) {
	long long int callCounter = 0;
	while (nth <= 80) {
		callCounter++;
		int i = nth / boardSize;
		int j = nth % *(boardColSize + i);
		int subBoxIndex = i / 3 * 3 + j / 3;
		char c = *(*(board + i) + j);
		// 回溯宫格的行 m,列 n,以及他是第几个宫格
		int m = -1;
		int n = -1;
		int minReCallNth = INT_MAX;
		if (c == '.') {
			findK(board, nth, i, j, subBoxIndex, 1, &m, &n, &minReCallNth, rows, cols, subBox, tag);
			// 如果找到数字，继续，否则回溯
			if (m == -1 && n == -1) {
				nth++;
			}
			else { // 没找到，回溯
				nth = minReCallNth;
			}
		}
		else {// 如果不是 . 有两种情况 1.题目给定的值，不做任何操作。2.回溯来的
			if (tag[i][j] == 0) { // 不可回溯，跳过
				nth++;
			}
			else { // 从 number+1 ~ 9 重新计算 k 的值
				int k = c - 48;
				rows[i][k] = 0;
				cols[j][k] = 0;
				subBox[subBoxIndex][k] = 0;
				*(*(board + i) + j) = '.';
				// 该节点无法回溯了，需要继续回溯上一个点
				if (k == 9) { 
					// 查找最近一个可回溯点，然后回溯
					for (int counter = nth - 1; counter >= 0; counter--) {
						int x = counter / boardSize;
						int y = counter % *(boardColSize + x);
						if (tag[x][y] == 1) {
							nth = counter;
							break;
						}
					}
				}
				else {
					findK(board, nth, i, j, subBoxIndex, k + 1, &m, &n, &minReCallNth, rows, cols, subBox, tag);
					// 如果找到数字，继续，否则回溯
					if (m == -1 && n == -1) {
						nth++;
					}
					else { // 没找到，回溯
						nth = minReCallNth;
					}
				}
			}
		}
	}
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
	// 表示第`i`行，数字`j`出现了多少次
	int rows[9][10] = { 0 };
	// 表示第`i`列，数字`j`出现了多少次
	int cols[9][10] = { 0 };

	// 表示第`i`个 sub box， 数字`j`出现了多少次
	// 对于任意的 board[i][j],我们可以知道它属于 第 `i/3 *3 + j / 3` subBox
	int subBox[9][10] = { 0 };

	// 表示board[i][j]个 元素是否可以回溯 0-不可用 1-可以
	int tag[9][9] = { 0 };
	initArray(board, boardSize, boardColSize, rows, cols,subBox, tag);
	solve(board, boardSize, boardColSize, 0, rows, cols, subBox, tag);
}

// 打印数独
void printBoard(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		char* s = *(board + i);
		for (int j = 0; j < *(boardColSize + i); j++) {
			printf("%c ", *(s + j));
		}
		printf("\n");
	}
}

// 将栈上的 board,改为堆分配，后期便于将 . 修改为具体的数字
char** initBoard(char b[][9]) {
	char** board = (char**)malloc(sizeof(char*) * 9);
	for (int i = 0; i < 9; i++) {
		char* s1 = (char*)malloc(sizeof(char) * 10);
		int j = 0;
		for (; j < 9; j++) {
			*(s1 + j) = b[i][j];
		}
		*(s1 + j) = '\0';
		*(board + i) = s1;
	}
	return board;
}

int main() {
	char b[][9] = {
		{'.','.','9','7','4','8','.','.','.'},
		{'7','.','.','.','.','.','.','.','.'},
		{'.','2','.','1','.','9','.','.','.'},
		{'.','.','7','.','.','.','2','4','.'},
		{'.','6','4','.','1','.','5','9','.'},
		{'.','9','8','.','.','.','3','.','.'},
		{'.','.','.','8','.','3','.','2','.'},
		{'.','.','.','.','.','.','.','.','6'},
		{'.','.','.','2','7','5','9','.','.'}
	};
	char** board = initBoard(&b);
	int boardSize = 9;
	int boardColSize[9] = { 0 };
	for (int i = 0; i < boardSize; i++) {
		boardColSize[i] = 9;
	}
	printBoard(board, boardSize, boardColSize);
	solveSudoku(board, boardSize, boardColSize);
	printBoard(board, boardSize, boardColSize);
	system("pause");
	return 0;
}
```

然后成功通过了，执行耗时 8ms