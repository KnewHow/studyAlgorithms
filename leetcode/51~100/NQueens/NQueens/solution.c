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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** res = (char***)malloc(sizeof(char**) * MAX_RETURN_SIZE);
    // 保存合法的位置，用于去重
    int** resArr = (int**)malloc(sizeof(int*) * MAX_RETURN_SIZE);
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
    takeUp(chessboard, 0, 0, n);
    while (*(pos + 0) < n) {
        if (nth == n) { // 所有的皇后已经找到对应的位置，保存结果
            int* newArray = copyArray(pos, n);
            quickSort(newArray, n);
            if (!isRepeat(resArr, *returnSize, newArray, n)) {
                *(res + *returnSize) = packageRes(pos, n);
                *(resArr + *returnSize) = newArray;
                *returnSize = *returnSize + 1;
            }
            // 继续回溯
            nth--;
            giveUp(chessboard, n, pos, nth);
        }
        else {
            if (nth < 0 || nth >= n) {
                printf("nth=%d\n", nth);
            }
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