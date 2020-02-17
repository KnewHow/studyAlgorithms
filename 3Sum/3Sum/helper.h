#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

void printArr(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", arr[i]);
		}
		else {
			printf("%d, ", arr[i]);
		}
		
	}
	printf(" ]\n");
}

void quickSortR(int* arr, int begin, int end) {
	if (end  > begin) { // ������Ԫ�ش��� 1 ����ʱ����
		int pivot = *(arr + begin);
		int left = begin;
		int right = end;
		while (left < right) {
			while (arr[right] >= pivot && left < right) {
				right--;
			}
			while (arr[left] <= pivot && left < right) {
				left++;
			}
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		int temp = arr[begin];
		arr[begin] = arr[left];
		arr[left] = temp;
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, right + 1, end);
	}
}

/**
* ��������
* @param arr ��������
* @param size �����С
*/
void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

/**
* ���ֲ���
* @param arr ��������
* @param size �����С
* @param value ��Ҫ���ҵ���
* @return ����ҵ���Ԫ�أ����ظ�Ԫ�صĽǱ꣬���򷵻� -1
*/
int binarySearch(int* arr, int size, int value) {
	int begin = 0;
	int end = size - 1;
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (*(arr + mid) == value) {
			return mid;
		}
		else if (value > *(arr + mid)) {
			begin = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	// û�ҵ�
	return -1; 
}

/**
* ��x,y,z���������մ�С�����˳�����һ��������
* @return һ�������������Ԫ�ص�����
*/
int* toSortedArray(int x, int y, int z) {
	int* arr = (int*)malloc(sizeof(int) * 3);
	*(arr + 0) = x;
	*(arr + 1) = y;
	*(arr + 2) = z;
	quickSort(arr, 3);
	return arr;
}

/**
* ��ԭ���鸴��һ���µ�����
*/
int* copyArray(int* nums, int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	int* p1 = arr;
	int* p2 = nums;
	while (p2 < nums + size) {
		*p1++ = *p2++;
	}
	return arr;
}

