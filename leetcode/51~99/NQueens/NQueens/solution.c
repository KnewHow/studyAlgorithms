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
    int n = 10;
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    char*** res = solveNQueens(n, &returnSize, &returnColumnSizes);
    printf("returnSize:%d\n", returnSize);
    // printRes(res, returnSize, returnColumnSizes);
	system("pause");
	return 0;
}