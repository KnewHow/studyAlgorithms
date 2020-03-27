#include<stdlib.h>
#include<stdio.h>
#define MAX_RETURN_SIZE 1024

/**
* �Ƿ��ǺϷ��� row �� col,nλ���̴�С
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
* �����̵� row �к͵� col ��λ�ñ��ʺ�ռ��
*/
void takeUp(char** chessboard, int row, int col, int n) {
    // ռ���к���
    for (int i = 0; i < n; i++) {
        *(*(chessboard + row) + i) = '1';
        *(*(chessboard + i) + col) = '1';
    }
    // ռ�������Խ���
    for (int i = 1; i < n; i++) {
        // ���Խ���
        int leadingBeforeRow = row - i;
        int leadingBeforCol = col - i;
        int leadingNextRow = row + i;
        int leadingNextCol = col + i;
        // б�Խ���
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
* ����ĳ���ʺ�����̵�ռ�ݣ�����������˼·��������Ҫ�����෴��˼·ȥִ�У�������������һЩ�ظ����ж�
* ���ǿ��Ի���˼·��ֻ��Ҫ������ʺ�֮ǰ�Ļʺ�����ռ�ݼ��ɡ�
* @param chessboard һ�� nxn �����̣������� Q ��ʾ�ʺ��λ�ã�1 ��ʾ�Ѿ�ռ�ݵ�λ�ã�0��ʾ����ռ�ݵ�λ��
* @param n ���̴�С
* @param pos һά���飬��ʾÿ���ʺ�ǰ�����������е�λ��
* @param currentQueen ��ǰ�ʺ��� pos �е� index
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
* �����̵Ľ����������
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
* ���ݷ�����˻ʺ�����
* @param chessboard һ�� nxn�����̣�Q ��ʾ�ʺ�1��ʾ�Ѿ���ռ���λ�� 0 ��ʾ����ռ���λ��
* @param row ��ǰ��Ҫ�� row �з���Ԫ��
* @param res �������ļ���
* @param returnSize ���ս������ size
* @param pos �洢ÿ�λʺ���õ�λ�ã���0~n^2-1,�������ȼ���
*/
void solve(char** chessboard, int row, int n, char ***res, int *returnSize, int *pos) {
    for (int col = 0; col < n; col++) {
        if (*(*(chessboard + row) + col) == '0') {// ����Ҵ���ʵ�λ�þ�ռ��֮
            takeUp(chessboard, row, col, n);
            int p = row * n + col;
            *(pos + row) = p;  // ��¼λ��
            if (row + 1 == n) { // ����Ѿ������еĻʺ����룬�����������������������һ�з��ûʺ�
                putToResult(chessboard, n, res, returnSize);
            }
            else
            {
                solve(chessboard, row + 1, n, res, returnSize, pos);
            }
            //�������ҵ�һ���⻹����һ���޷��ҵ����ʵ�λ�ã����Ƕ����л���
            giveUp(chessboard, n, pos, row);
        }
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** res = (char***)malloc(sizeof(char**) * MAX_RETURN_SIZE);
    // ����Ϸ���λ�ã�����ȥ��
    *returnSize = 0;
    /*
    * ��ʼ��һ�� n x n �����̣����ڻ��ݡ�
    * ��ĳ�����ӵ�ֵ 0 ʱ����ʾ���Է���Queen��1 ��ʾ���ܿ��Է��� Queen, Q ��ʾ��λ���Ѿ�������һ�� Queen
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