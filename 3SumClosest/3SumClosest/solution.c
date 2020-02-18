#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include"hashTable.h"

/**
* 暴力法，三层循环计算任意三个数之和，取其和 target 距离最近的那个
*
*/
int threeSumClosestFource(int* nums, int numsSize, int target) {
	int distans = INT_MAX;
	int sum = 0;
	for (int x = 0; x < numsSize; x++) {
		for (int y = x + 1; y < numsSize; y++) {
			for (int z = y + 1; z < numsSize; z++) {
				int s = nums[x] + nums[y] + nums[z];
				int dis = abs(target - s);
				if (dis < distans) {
					distans = dis;
					sum = s;
				}
			}
		}
	}
	return sum;
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


/**
* 参考了网上的题解，做法比我的简单很多，首先对原数组排序，然后遍历
* 当遍历到第 i 个元素时，开始从 i+1 ~ end，对数组进行迭代，
* 如果 sum > taget,end --，否则 begin++,直到 begin > end
* 当然时间复杂度为 O(n^2)
* 
*/
int threeSumClosest(int* nums, int numsSize, int target) {
	quickSort(nums, numsSize);
	int sum = nums[0] + nums[1] + nums[2];
	for (int i = 0; i < numsSize; i++) {
		int begin = i + 1;
		int end = numsSize - 1;
		while (begin < end) {
			int s = nums[i] + nums[begin] + nums[end];
			if (abs(target - sum) > abs(target - s)) {
				sum = s;
			}
			if (s > target) {
				end--;
			}
			else {
				begin++;
			}
		}
	}
	return sum;
}

int main() {
	int arr[] = { -1, 2, 1, -4 };
	int size = sizeof(arr) / sizeof(int);
	int target = 1;
	int r = threeSumClosest(arr, size, target);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}