# Find First and Last Position of Element in Sorted Array

Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

我们可以使用二分查找在`O(logN)`的时间复杂度内找打该元素，然后我们从该位置开始，分别往前，往后使用翻倍法来寻常和该元素相等的角标。还记得我们之前做过的两数相除的翻倍法，可以以`2^n`逼近一个数，这里我们就用到了这个方法。

```c
#include<stdlib.h>
#include<stdio.h>


/**
* 从 mid 的位置往前找，找到 target 第一次出现的位置减量，使用的是每次翻倍的思想，
* 以 2^n 的速度逼近
* @param nums 原正序排序的数组
* @param numsSize 数组大小
* @param target 目标数
* @param mid 目标数所在的一个角标
* @param 返回 target 在数组 nums 中首次出现的角标
*/
int findFirstPositionDecrease(
	int* nums, 
	int numsSize, 
	int target, 
	int mid
) {
	// 每次从 1 开始翻倍
	int tb = 1;
	int counter = 1;
	if (mid - tb < 0) {
		return 0;
	}
	if (*(nums + mid - tb) != target) {
		return 0;
	}
	while (mid - 2 * tb >= 0 && *(nums + mid - 2 * tb) == target) {
		tb += tb;
		counter += counter;
	}
	return counter + findFirstPositionDecrease(nums, numsSize, target, mid - counter);
}

/**
 从 mid 的位置往后找，找到 target 最后一次出现的位置增量
*/
int findLastPositionIncrease(
	int* nums,
	int numsSize,
	int target,
	int mid) {
	int tb = 1;
	if (mid + tb >= numsSize) {
		return 0;
	}
	if (*(nums + mid + tb) != target) {
		return 0;
	}
	int counter = 1;
	while (mid + 2 * tb < numsSize && *(nums + mid + 2 * tb) == target) {
		counter += counter;
		tb += tb;
	}
	return counter + findLastPositionIncrease(nums, numsSize, target, mid + counter);
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	*returnSize = 2;
	int* r = (int*)malloc(sizeof(int) * 2);
	int begin = 0;
	int end = numsSize - 1;
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (target  == *(nums + mid)) {
			int firstDecrease = findFirstPositionDecrease(nums, numsSize, target, mid);
			int lastIncrease = findLastPositionIncrease(nums, numsSize, target, mid);
			*(r + 0) = mid - firstDecrease;
			*(r + 1) = mid + lastIncrease;
			return r;
		}
		else if (target < *(nums + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	// 没有找到
	*(r + 0) = -1;
	*(r + 1) = -1;
	return r;
}

void printArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d, ", *(arr + i));
		}
	}
	printf(" ]\n");
}

int main() {
	int nums[] = { 1 };
	int size = sizeof(nums) / sizeof(int);
	int target = 1;
	int returnSize = 0;
	int* r = searchRange(nums, size, target, &returnSize);
	printArray(r, returnSize);
	system("pause");
	return 0;
}
```

