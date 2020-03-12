#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

void printArray(int* arr, int size) {
	printf("[");
	for (int j = 0; j < size; j++) {
		if (j == size - 1) {
			printf("%d ", *(arr + j));
		}
		else {
			printf("%d, ", *(arr + j));
		}
	}
	printf("]\n");
}

void printRes(int** res, int rows, int* cols) {
	printf("[\n");
	for (int i = 0; i < rows; i++) {
		int* arr = *(res + i);
		int col = *(cols + i);
		printf("\t");
		printArray(arr, col);
	}
	printf("]\n");
}

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

/**
* ʹ�õݹ鷨���
*/
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
		swap(arr, begin, left);
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

void addToRes(int* nums, int numsSize, int** res, int* returnSize) {
	int* arr = (int*)malloc(sizeof(int) * numsSize);
	for (int i = 0; i < numsSize; i++) {
		*(arr + i) = *(nums + i);
	}
	*(res + *returnSize) = arr;
	*returnSize = *returnSize + 1;
}

/**
* �������е��ֵ�����
*/
void generateAllLexicographically(int* nums, int numsSize, int** res, int* returnSize) {
	addToRes(nums, numsSize, res, returnSize);
	while (1) {
		int k = -1;
		// �ҵ� k,ʹ�� nums[k] < nums[k+1]
		for (int i = 0; i < numsSize - 1; i++) {
			if (*(nums + i) < *(nums + i + 1)) {
				k = i;
			}
		}
		if (k == -1) {  // ˵����ʱ�������Ѿ�ȫ��Ϊ�����ֵ������ɽ���
			break;
		}
		else { // ˵�� nums ������һ��������ֵ���
			int min = *(nums + k + 1);
			int pos = k + 1;
			// �� k+1 �������ң��ҵ�һ���� a,ʹ�� a[k] < a < a[k+1]
			for (int i = k + 1; i < numsSize; i++) {
				int temp = *(nums + i);
				if (temp > * (nums + k) && temp < min) {
					min = temp;
					pos = i;
				}
			}
			// ���� k �� pos λ��
			swap(nums, k, pos);
			// �� k+1 ~ numsSize-1 ֮���Ԫ�ؽ��з�ת
			int mid = (k + 1 + numsSize) / 2;
			for (int i = k + 1; i < mid; i++) {
				int _i = numsSize - i + k;
				swap(nums, i, _i);
			}
			addToRes(nums, numsSize, res, returnSize);
		}
	}
}

/**
* ʹ���ֵ������
*/
int** permute2(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	int total = factorial(numsSize);
	*returnSize = total;
	*(returnColumnSizes) = (int*)malloc(sizeof(int) * total);
	for (int i = 0; i < total; i++) {
		*(*(returnColumnSizes)+i) = numsSize;
	}
	int** res = (int**)malloc(sizeof(int*) * total);
	quickSort(nums, numsSize);
	int size = 0;
	generateAllLexicographically(nums, numsSize, res, &size);
	*returnSize = size;
	return res;
}


int main() {
	int nums[] = { 1,1,2 };
	int size = sizeof(nums) / sizeof(int);
	int rows = 0;
	int* cols = NULL;
	int** res = permute2(nums, size, &rows, &cols);
	printRes(res, rows, cols);
	system("pause");
	return 0;
}