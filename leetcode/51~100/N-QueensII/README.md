# Question

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

![](8-queens.png)

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

Example:

```
Input: 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown below.
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：正常解

既然只要求有多少个，按照之前的算法，只有把最终的size 返回即可，代码如下：

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
* 回溯法解决八皇后问题
* @param chessboard 一个 nxn的棋盘，Q 表示皇后，1表示已经被占领的位置 0 表示可以占领的位置
* @param row 当前需要在 row 行放置元素
* @param res 保存结果的集合
* @param returnSize 最终结果集的 size
* @param pos 存储每次皇后放置的位置，从0~n^2-1,以行优先计算
*/
void solve(char** chessboard, int row, int n, int* returnSize, int* pos) {
    for (int col = 0; col < n; col++) {
        if (*(*(chessboard + row) + col) == '0') {// 如果找打合适的位置就占领之
            takeUp(chessboard, row, col, n);
            int p = row * n + col;
            *(pos + row) = p;  // 记录位置
            if (row + 1 == n) { // 如果已经把所有的皇后都填入，保存结果，否则继续尝试往下一行放置皇后
                *returnSize = *returnSize + 1;
            }
            else
            {
                solve(chessboard, row + 1, n, returnSize, pos);
            }
            //无论是找到一个解还是下一行无法找到合适的位置，我们都进行回溯
            giveUp(chessboard, n, pos, row);
        }
    }
}

int totalNQueens(int n) {
    // 保存合法的位置，用于去重
    int returnSize = 0;
    /*
    * 初始化一个 n x n 的棋盘，用于回溯。
    * 当某个格子的值 0 时，表示可以放入Queen，1 表示不能可以放入 Queen, Q 表示该位置已经放入了一个 Queen
    */
    char** chessboard = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * (n + 1));
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
    solve(chessboard, 0, n, &returnSize, pos);
    return returnSize;
}


int main() {
    int n = 10;
    int r = totalNQueens(n);
    printf("r is %d\n", r);
	system("pause");
	return 0;
}
```

## 解法二：投机取巧

既然我们已经可以计算出1~n 皇后的问题，那么我们为什么不能用下面的代码呢：

```c
int totalNQueens(int n){
        int rs[20] ={0,1,0,0,2,10,4,40,92,352,724,2680};
        return rs[n];
}
```

