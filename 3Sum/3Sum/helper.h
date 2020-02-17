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
	if (end  > begin) { // 当数组元素大于 1 个的时候做
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
* 快速排序
* @param arr 给定数组
* @param size 数组大小
*/
void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

/**
* 二分查找
* @param arr 有序数组
* @param size 数组大小
* @param value 需要查找的数
* @return 如果找到该元素，返回该元素的角标，否则返回 -1
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
	// 没找到
	return -1; 
}

/**
* 将x,y,z三个数按照从小到大的顺序放入一个数组中
* @return 一个存放三个有序元素的数组
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
* 由原数组复制一个新的数组
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

