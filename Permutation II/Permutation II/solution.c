#include<stdlib.h>
#include<stdio.h>

/**
* ���� n �� �׳�
*/
int clcNFactory(int n) {
	if (n < 1) {
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
* ����������Ԫ��
*/

void swap(int* arr, int idx1, int idx2) {
	int temp = *(arr + idx1);
	*(arr + idx1) = *(arr + idx2);
	*(arr + idx2) = temp;
}

/**
* ��������ݹ���
*/
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

void printArray(int* arr, int size) {
	printf("[");
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

void printTwoDimenArray(int** res, int rows, int* cols) {
	printf("[\n");
	for (int i = 0; i < rows; i++) {
		int* arr = *(res + i);
		int col = *(cols + i);
		printf("\t");
		printArray(arr, col);
	}
	printf("]\n");
}

void addToRes(int* nums, int numsSize, int** res, int* returnSize) {
	int* arr = (int*)malloc(sizeof(int) * numsSize);
	for (int i = 0; i < numsSize; i++) {
		*(arr + i) = *(nums + i);
	}
	*(res + *returnSize) = arr;
	*returnSize = *returnSize + 1;
}

int isSwap(int* nums, int numsSize, int nth) {
	for (int i = nth + 1; i < numsSize; i++) {
		if (*(nums + nth) == *(nums + i)) {
			return 0;
		}
	}
	return 1;
}

/**
* �ݹ�ļ������ظ��������ȫ����
* @param nums ԭ����
* @param numsSize 
* @param res ���ÿ�μ���Ľ��,һ����ά���飬
* @param returnSize res size�ĵ�ַ����ʼ��Ϊ 0
* @param nth ��ǰѡ���� nth ��Ԫ��
*/
void doPermuteUnique(int* nums, int numsSize, int** res, int* returnSize, int nth) {
	if (nth == numsSize) {
		addToRes(nums, numsSize, res, returnSize);
	}
	else {
		for (int i = nth; i < numsSize; i++) {
			if (isSwap(nums, numsSize, i)) {
				swap(nums, nth, i);
				doPermuteUnique(nums, numsSize, res, returnSize, nth + 1);
				swap(nums, nth, i);
			}
		}
	}
}

/**
* ʹ�õݹ�ķ���������ظ���������ȫ����
*/
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	// �������ظ����������˵�����Ҳ�� numsSize! ��
	int total = clcNFactory(numsSize);
	int size = 0;
	int** res = (int**)malloc(sizeof(int*) * total);
	doPermuteUnique(nums, numsSize, res, &size, 0);
	*returnSize = size;
	*(returnColumnSizes) = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(*(returnColumnSizes)+i) = numsSize;
	}
	return res;
}

/**
* �������е��ֵ���
* @param nums ԭ����
* @param numsSize
* @param res ���ÿ�μ���Ľ��,һ����ά���飬
* @param returnSize res size�ĵ�ַ����ʼ��Ϊ 0
*/
void generateLexicographical(int* nums, int numsSize, int** res, int* returnSize) {
	addToRes(nums, numsSize, res, returnSize);
	while (1) {
		int k = -1;
		for (int i = 0; i < numsSize - 1; i++) {
			if (*(nums + i) < *(nums + i + 1)) {
				k = i;
			}
		}

		if (k == -1) {
			break;
		}
		else {
			int min = *(nums + k + 1);
			int pos = k + 1;
			for (int i = k + 1; i < numsSize; i++) {
				if (*(nums + i) > * (nums + k) && *(nums + i) <= min) {
					min = *(nums + i);
					pos = i;
				}
			}
			swap(nums, k, pos);
			int mid = (k + 1 + numsSize) / 2;
			for (int i = k + 1; i < mid; i++) {
				int _i = numsSize + k - i;
				swap(nums, i, _i);
			}
			addToRes(nums, numsSize, res, returnSize);
		}
	}
}

int** permuteUnique2(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	int total = clcNFactory(numsSize);
	int size = 0;
	int** res = (int**)malloc(sizeof(int*) * total);
	quickSort(nums, numsSize);
	generateLexicographical(nums, numsSize, res, &size);
	*(returnColumnSizes) = (int*)malloc(sizeof(int) * size);
	*returnSize = size;
	for (int i = 0; i < size; i++) {
		*(*(returnColumnSizes)+i) = numsSize;
	}
	return res;
}

int main() {
	int nums[] = { 2,2,1,1 };
	int size = sizeof(nums) / sizeof(int);
	int rows = 0;
	int* cols = NULL;
	int **r = permuteUnique2(nums, size, &rows, &cols);
	printTwoDimenArray(r, rows, cols);
	system("pause");
	return 0;
}