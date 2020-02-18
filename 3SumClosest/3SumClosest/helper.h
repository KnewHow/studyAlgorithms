#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

/**
* 拷贝数组并返回
* @param nums 原数组头指针
* @param size 数组大小
* @return 返回新数组
*/
int* copyArray(int* nums, int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	int* p1 = nums;
	int* p2 = arr;
	while (p1 < nums + size) {
		*p2++ = *p1++;
	}
	return arr;
}

/**
* 快速排序的递归调用函数
* @param nums 待排序数组
* @param begin 数组开始角标
* @param end 数组结束角标
*/
void quickSortR(int* nums, int begin, int end) {
	if (end - begin > 0) { // 当数组的元素超过两个时才进行排序
		int left = begin;
		int right = end;
		int pivot = nums[begin]; // 用第一个元素当主元
		while (left < right) {
			while (*(nums + right) >= pivot && left < right) {
				right--;
			}
			while (*(nums + left) <= pivot && left < right) {
				left++;
			}
			int temp = *(nums + left);
			*(nums + left) = *(nums + right);
			*(nums + right) = temp;
		}
		int temp = *(nums + begin);
		*(nums + begin) = *(nums + left);
		*(nums + left) = temp;
		quickSortR(nums, begin, left - 1);
		quickSortR(nums, left + 1, end);
	}
}

/**
* 快速排序
* @param nums 原始数组
* @param size 数组大小
*/
void quickSort(int* nums, int size) {
	quickSortR(nums, 0, size - 1);
}
