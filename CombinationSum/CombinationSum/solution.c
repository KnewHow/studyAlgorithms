#include<stdlib.h>
#include<stdio.h>
#include "queue.h"
#define MAX_SIZE 1000

void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
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

int* toArray(PQueue queue, int *size) {
	int* arr = (int*)malloc(sizeof(int) * MAX_SIZE);
	*size = 0;
	PElement p = queue->head;
	while (p != NULL) {
		*(arr + *size) = p->value;
		*size = *size + 1;
		p = p->next;
	}
	return arr;
}

/**
* �ݹ�ļ������е�����
* @param candidates ������õĴ�ѡ����
* @param candidatesSize �����С
* @param target Ŀ������
* @param begin ÿ�δ� candidates �� begin �±꿪ʼ
* @param returnSize ���շ��ؽ�������� size ��ַ
* @param returnColumnSize ÿ����������Ĵ�С
* @param res �������ս�����Ķ�ά����
* @param queue �洢�м����Ķ���
*/
void solve(
	int* candidates,
	int candidatesSize,
	int target,
	int begin,
	int* returnSize,
	int* returnColumnSizes,
	int** res,
	PQueue queue
) {
	if (target == 0) {
		int size = 0;
		*(res + *returnSize) = toArray(queue, &size);
		*(returnColumnSizes + *returnSize) = size;
		*returnSize = *returnSize + 1;
	}
	else {
		for (int i = begin; i < candidatesSize; i++) {
			// ��� target - candidates[i] < 0,�������������������ܣ�����ѭ��
			if (target - *(candidates + i) < 0) {
				break;
			}
			int value = *(candidates + i);
			putLast(queue, *(candidates + i));
			solve(
				candidates,
				candidatesSize,
				target - value,
				i,
				returnSize,
				returnColumnSizes, 
				res, 
				queue
			);
			removeLast(queue);
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(
	int* candidates, 
	int candidatesSize, 
	int target, 
	int* returnSize, 
	int** returnColumnSizes) {
	PQueue queue = newQueue();
	int** res = (int**)malloc(sizeof(int*) * MAX_SIZE);
	*returnSize = 0;
	*returnColumnSizes = (int*)malloc(sizeof(int) * MAX_SIZE);
	quickSort(candidates, candidatesSize);
	solve(candidates, 
		candidatesSize, 
		target, 
		0, 
		returnSize, 
		*returnColumnSizes, 
		res, 
		queue
	);
	return res;
	
}

void printTwoDimensionalArray(int** res, int size, int* colSizes) {
	printf("[\n");
	for (int i = 0; i < size; i++) {
		int colSize = *(colSizes + i);
		printf("\t[");
		int* arr = *(res + i);
		for (int j = 0; j < colSize; j++) {
			if (j == colSize - 1) {
				printf("%d", *(arr + j));
			}
			else {
				printf("%d,", *(arr + j));
			}
		}
		printf("]\n");
	}
	printf("]\n");
}

int main() {
	int candidates[] = { 2,3,6,7 };
	int target = 7;
	int returnSize = 0;
	int* returnColumnSizes;
	int candidatesSize = sizeof(candidates) / sizeof(int);
	int** res = combinationSum(candidates, candidatesSize, target, &returnSize, &returnColumnSizes);
	printTwoDimensionalArray(res, returnSize, returnColumnSizes);
	system("pause");
	return 0;
}