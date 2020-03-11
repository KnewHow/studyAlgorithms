#include<stdio.h>
#include<stdlib.h>

int** copy(int** matrix, int matrixSize, int* matrixColSize) {
	int** r = (int**)malloc(sizeof(int*) * matrixSize);
	for (int i = 0; i < matrixSize; i++) {
		int col = *(matrixColSize + i);
		int* row = (int*)malloc(sizeof(int) * col);
		for (int j = 0; j < col; j++) {
			*(row + j) = *(*(matrix + i) + j);
		}
		*(r + i) = row;
	}
	return r;
}

void freeMatrix(int** matrix, int matrixSize, int* matrixColSize) {
	for (int i = 0; i < matrixSize; i++) {
		int* row = *(matrix + i);
		free(row);
	}
	free(matrix);
}

/**
* 创建一个额外矩阵的做法
*/
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
	int** _matrix = copy(matrix, matrixSize, matrixColSize);
	for (int i = 0; i < matrixSize; i++) {
		int row = *(matrix + i);
		int col = matrixSize - 1 - i;
		for (int j = 0; j < matrixSize; j++) {
			*(*(_matrix + j) + col) = *(*(matrix + i) + j);
		}
	}
	for (int i = 0; i < matrixSize; i++) {
		int* arr = *(_matrix + i);
		int col = *(matrixColSize + i);
		for (int j = 0; j < col; j++) {
			*(*(matrix + i) + j) = *(*(_matrix + i) + j);
		}
	}
	freeMatrix(_matrix, matrixSize, matrixColSize);
}

void printMatrix(int** matrix, int matrixSize, int* matrixColSize) {
	printf("[\n");
	for (int i = 0; i < matrixSize; i++) {
		int* row = *(matrix + i);
		int col = *(matrixColSize + i);
		printf("\t[");
		for (int j = 0; j < col; j++) {
			if (j == col - 1) {
				printf("%d ", *(row + j));
			}
			else {
				printf("%d, ", *(row + j));
			}
		}
		printf("]\n");
	}
	printf("]\n");
}

/**
* 二位数组元素位置交换
*/
void swapTwoDeci(int** matrix, int row1, int col1, int row2, int col2) {
	int temp = *(*(matrix + row1) + col1);
	*(*(matrix + row1) + col1) = *(*(matrix + row2) + col2);
	*(*(matrix + row2) + col2) = temp;
}

/**
* 先转置，在对每行进行反转
*/
void rotate2(int** matrix, int matrixSize, int* matrixColSize) {
	int n = matrixSize;
	for (int i = 0; i < n; i++) {
		// 旋转只需要旋转上三角矩阵即可
		for (int j = i; j < n; j++) {
			swapTwoDeci(matrix, i, j, j, i);
		}
	}
	for (int i = 0; i < n; i++) {
		int mid = n / 2;
		for (int j = 0; j < mid; j++) {
			swapTwoDeci(matrix, i, j, i, n - j - 1);
		}
	}
}


int** creatMatrix() {
	int matrix[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9},
	};
	int** r = (int**)malloc(sizeof(int*) * 3);
	for (int i = 0; i < 3; i++) {
		int* row = (int*)malloc(sizeof(int) * 3);
		for (int j = 0; j < 3; j++) {
			*(row + j) = matrix[i][j];
		}
		*(r + i) = row;
	}
	return r;
}

int main() {
	int** matrix = creatMatrix();
	int matrixSize = 3;
	int matrixColSize[3] = { 3,3,3 };
	rotate2(matrix, matrixSize, matrixColSize);
	printMatrix(matrix, matrixSize, matrixColSize);
	system("pause");
	return 0;
}