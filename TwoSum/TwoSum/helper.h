#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<time.h>

// 辅助函数-打印数组
void printArray(int* p, int numsSize) {
	for (int* i = p; (i - p) < numsSize; i++) {
		printf("%d ", *i);
	}
	printf("\n");
}

// 辅助函数-数组copy
int* copyArray(int* nums, int numsSize) {
	int* p = NULL;
	p = (int*)malloc(numsSize * sizeof(int));
	if (p != NULL) {
		for (int* i = nums; i < nums + numsSize; i++) {
			p[i - nums] = *i;
		}
		return p;
	}
	else
	{
		return NULL;
	}
}

// 扶助函数-快速排序
void quickSort(int* nums, int left, int right) {
	if (right - left > 1) {
		int pivod = nums[left];
		int i = left;
		int j = right;
		while (i < j) {
			while (nums[j] >= pivod && i < j) {
				j--;
			}
			while (nums[i] <= pivod && i < j) {
				i++;
			}
			int temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}
		int temp = nums[left];
		nums[left] = nums[i];
		nums[i] = temp;
		quickSort(nums, left, i - 1);
		quickSort(nums, j + 1, right);
	}
}

// 辅助函数-二分查找
int binarySearch(int* nums, int numsSize, int target) {
	int isFound = 1;
	int left = 0;
	int right = numsSize - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (nums[mid] == target) {
			return mid;
		}
		else if (nums[mid] > target) {
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return -1;
}

long int getCurrentMills() {
	time_t t;
	time(&t);
	// printf("time=%d\n", t);
	return t;
}