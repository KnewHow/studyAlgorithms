#include<stdlib.h>
#include<stdio.h>
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

        if (isLegalRowAndCol(leadingBeforeRow, leadingBeforeRow,n)) {
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
* �ӵ�ǰλ�� begin ��������Ѱ��һ�����Է��� Queen �ĸ��ӣ������أ�����Ҳ��������� -1
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** res = (char***)malloc(sizeof(char**) * MAX_RETURN_SIZE);
    // ����Ϸ���λ�ã�����ȥ��
    int** resArr = (int**)malloc(sizeof(int*) * MAX_RETURN_SIZE);
    *returnSize = 0;
    /* 
    * ��ʼ��һ�� n x n �����̣����ڻ��ݡ�
    * ��ĳ�����ӵ�ֵ 0 ʱ����ʾ���Է���Queen��1 ��ʾ���ܿ��Է��� Queen, Q ��ʾ��λ���Ѿ�������һ�� Queen
    */
    char** chessboard = (char**)malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        char* row = (char*)malloc(sizeof(char) * n);
        for (int j = 0; j < n; j++) {
            *(row + j) = '0';
        }
        *(chessboard + i) = row;
    }
    /** ��ʼһ������λ n ������������¼ÿ�� Queen ��λ�ã�
    * ��(0,0) ~ (n-1, n-1),����Ϊ���ȣ����ΰѸ��ӱ��Ϊ 0��1,2,3 ... n^2-1
    */
    int* pos = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        *(pos + i) = -1;
    }
    // �����̵�һ��λ��(0,0)��ʼ
    *(*(chessboard + 0) + 0) = 'Q';
    *(pos + 0) = 0;
    // ��ǰ����Ѱ�ҵ� nth ���ʺ�
    int nth = 1;
    takeUp(chessboard, 0, 0, n);
    while (*(pos + 0) < n) {
        if (nth == n) { // ���еĻʺ��Ѿ��ҵ���Ӧ��λ�ã�������
            int* newArray = copyArray(pos, n);
            quickSort(newArray, n);
            if (!isRepeat(resArr, *returnSize, newArray, n)) {
                *(res + *returnSize) = packageRes(pos, n);
                *(resArr + *returnSize) = newArray;
                *returnSize = *returnSize + 1;
            }
            // ��������
            nth--;
            giveUp(chessboard, n, pos, nth);
        }
        else {
            if (nth < 0 || nth >= n) {
                printf("nth=%d\n", nth);
            }
            int currentPos = *(pos + nth);
            int p = findEnablePosition(chessboard, currentPos + 1, n);
            if (p != -1) { // �ҵ�һ�����ʵ�λ��,��������һ��
                int row = p / n;
                int col = p % n;
                *(pos + nth) = p;
                takeUp(chessboard, row, col, n);
                nth++;
            }
            else { // û�ҵ����ʵ�λ�ã�����
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
    int n = 4;
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    char*** res = solveNQueens(n, &returnSize, &returnColumnSizes);
    printRes(res, returnSize, returnColumnSizes);
	system("pause");
	return 0;
}