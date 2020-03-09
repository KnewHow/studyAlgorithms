#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

// ���� n!
int factorial(int n) {
	if (n == 0) {
		return 0;
	}
	else {
		int r = 1;
		for (int i = n; i >= 1; i--) {
			r *= i;
		}
		return r;
	}
}

/**
* �������������Ǳ��Ԫ��
*/
void swap(int* arr, int idx1, int idx2) {
	int temp = *(arr + idx1);
	*(arr + idx1) = *(arr + idx2);
	*(arr + idx2) = temp;
}

/**
* �ݹ���������� nums ��ȫ����
* @param nums ԭ����
* @param numsSize ԭ�����С
* @param res ����������еĽ��
* @size res size �ĵ�ַ
* @param ��ǰ�� nth ��Ԫ��
*/
void doPermutes(int* nums, int numsSize, int** res, int* size, int nth) {
	if (nth == numsSize) { // Ԫ��ȫ��ȡ��
		int* arr = (int*)malloc(sizeof(int) * numsSize);
		for (int i = 0; i < numsSize; i++) {
			*(arr + i) = *(nums + i);
		}
		*(res + *size) = arr;
		*size = *size + 1;
	}
	else {
		for (int i = nth; i < numsSize; i++) {
			// ����λ�ã��൱�� nth �ֱ�ȡ(nth ~ numsSize-1) ��Ԫ�أ�Ȼ��ݹ�Ľ����һ��λ��
			swap(nums, nth, i);
			doPermutes(nums, numsSize, res, size, nth + 1);
			// ���Ҫ��������
			swap(nums, nth, i);
		}
	}
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	int total = factorial(numsSize);
	*returnSize = total;
	*(returnColumnSizes) = (int*)malloc(sizeof(int) * total);
	for (int i = 0; i < total; i++) {
		*(*(returnColumnSizes)+i) = numsSize;
	}
	int** res = (int**)malloc(sizeof(int*) * total);
	int size = 0;
	doPermutes(nums, numsSize, res, &size, 0);
	return res;
}

void printRes(int** res, int rows, int* cols) {
	printf("[\n");
	for (int i = 0; i < rows; i++) {
		int* arr = *(res + i);
		int col = *(cols + i);
		printf("\t[");
		for (int j = 0; j < col; j++) {
			if (j == col - 1) {
				printf("%d ", *(arr + j));
			}
			else {
				printf("%d, ", *(arr + j));
			}
		}
		printf("]\n");
	}
	printf("]\n");
}

int main() {
	int nums[] = { 1,2,3 };
	int size = sizeof(nums) / sizeof(int);
	int rows = 0;
	int* cols = NULL;
	int** res = permute(nums, size, &rows, &cols);
	printRes(res, rows, cols);
	system("pause");
	return 0;
}