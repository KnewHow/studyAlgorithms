#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

// 打印数组
void printArr(int* nums, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", nums[i]);
		}
		else {
			printf("%d, ", nums[i]);
		}
	}
	printf(" ]\n");
}

void quickSortR(int* nums, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = nums[begin];
		while (left < right) {
			while (left < right && *(nums + right) >= pivot) {
				right--;
			}
			while (left < right && *(nums + left) <= pivot) {
				left++;
			}
			int temp = *(nums + left);
			*(nums + left) = *(nums + right);
			*(nums + right) = temp;
		}
		int temp = *(nums + left);
		*(nums + left) = *(nums + begin);
		*(nums + begin) = temp;
		quickSortR(nums, begin, left - 1);
		quickSortR(nums, left + 1, end);
	}
	
}

// 快速排序
void quickSort(int* nums, int size) {
	quickSortR(nums, 0, size - 1);
}

/**
* 三数之和
* @param nums 原数组
* @param numsSize 数组大小
* @param target 目标数
* @param a 已经确定的数 a
* @param aIndex a在 num 数组中的角标
* @param r 存储结果的二维数组，每个数组中有四个元素
* @param counter 计数器，用于统计 r 的 size
*/

void threeSum(
	int* nums,
	int numsSize,
	int target,
	int a,
	int aIndex,
	int** r,
	int *counter
) {
	for (int i = aIndex + 1; i < numsSize; i++) {
		int left = i + 1;
		int right = numsSize - 1;
		// 只有当 i 比当前 a角标+1 还大的时候，才能去重，否则会把[0,0,0] 给去掉的
		if (i > aIndex + 1 && nums[i] == nums[i - 1]) {
			continue;
		}
		while (left < right) {
			int sum = nums[i] + nums[left] + nums[right];
			if (sum == target) {
				int* arr = (int*)malloc(sizeof(int) * 4);
				*(arr + 0) = a;
				*(arr + 1) = nums[i];
				*(arr + 2) = nums[left];
				*(arr + 3) = nums[right];
				*(r + *counter) = arr;
				*counter = *counter + 1;
				// 去重
				while (left < right && nums[left] == nums[left + 1]) {
					left++;
				}
				while (left < right && nums[right] == nums[right - 1]) {
					right--;
				}
				left++;
				right--;
			}
			else if (sum > target) {
				right--;
			}
			else {
				left++;
			}
		}
	}
}


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, 
 * assume caller calls free().
 * 还记得之前三个数之和吗，我们可以先遍历一遍数组，int sum = target-nums[i]
 * 转换为三数之和
 */
int** fourSum(
	int* nums, 
	int numsSize, 
	int target, 
	int* returnSize, 
	int** returnColumnSizes
) {
	int** r = (int**)malloc(sizeof(int*) * 1024);
	int counter = 0;
	quickSort(nums, numsSize);
	for (int i = 0; i < numsSize; i++) {
		int sum = target - nums[i];
		// 去掉重复元素
		if (i > 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		threeSum(nums, numsSize, sum, nums[i],i, r, &counter);
	}
	*returnSize = counter;
	int* colums = (int*)malloc(sizeof(int) * counter);
	for (int* p = colums; p < colums + counter; p++) {
		*p = 4;
	}
	*returnColumnSizes = colums;
	return r;
}


int main() {
	int nums[] = { 1,-2,-5,-4,0,0,0,0,-3,3,3,5 };
	int size = sizeof(nums) / sizeof(int);
	int target = 0;
	int returnSize = 0;
	int* returnColumnSizes = NULL;
	int** r = fourSum(nums, size, target,&returnSize, &returnColumnSizes);
	printf("[\n");
	for (int i = 0; i < returnSize; i++) {
		printf("\t");
		printArr(*(r + i), *(returnColumnSizes + i));
	}
	printf("]\n");
	system("pause");
	return 0;
}