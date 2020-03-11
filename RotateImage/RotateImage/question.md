# Rotate Image

You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

Example 1:

```
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
```

Example 2:

```
Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
```



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-image
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：创建一个新矩阵

虽说题目不允许开辟一个新的矩阵，但是我觉着嘛，用一个新矩阵更容易理解。就是第一行变成最后一列，第二行变成倒数第二列，最后一行变成了第一列。

```c
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
```



## 解法二：先转置，然后反转每一行

参考官方题解的做法，先转置，在反转。

```c
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
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
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
```

