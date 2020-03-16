#include<stdio.h>
#include<stdlib.h>

/**
* 那我们如何找到数组的分界线呢？ 我们知道，对于 nums 的两个有序子数组来说
* 都有 a[i] < a[i+1],但是对于分界点 j 来说，会存在 a[j] > a[j+1]
* 我们当然可以遍历一遍 nums 数组，找到 a[j] > a[j+1] 的点,
* 可是这样的时间复杂度就是 O(N),无法达到题目要求的O(logN),有没有更快的方法?
* 
* 考虑一下我们的二分查找的思路，我们先定义一个 pivot = (begin + end) / 2
* 如果 nums[pivot] > nums[pivot+1],说明在 povit 点数组被分成两个数组。
* 否则，我们需要比较 nums[pivot] > nums[begin]。如果 a[pivot] > nums[begin]
* 说明 pivot 还在第一个有序的数组内，分界点在右半边，让 begin = pivot
* 否则说明 pivot 已经在第二个有序数组内，分界点在左半边，让 end = pivot
*
* 在此函数中，我们返回分界点的最小元素的角标
*/
int findSmallestIndex(int* nums, int size) {
	int begin = 0;
	int end = size - 1;
	// 如果 nums[0] < nums[size-1],说明数组本身就是有序的，直接返回 0
	if (*(nums + begin) <= *(nums + end)) {
		return 0;
	}
	else {
		while (begin <= end) {
			int pivot = (begin + end) / 2;
			if (*(nums + pivot) >= *(nums + pivot + 1)) {
				return pivot + 1;
			}
			else if (*(nums + pivot) > * (nums + begin)) {
				begin = pivot;
			}
			else {
				end = pivot;
			}
		}
		return -1;
	}
}

// 二分搜索
int binarySearch(int* arr, int begin, int end, int target) {
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (target  == *(arr + mid)) {
			return mid;
		}
		else if (target < *(arr + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	return -1;
}

/**
* 对于 nums 数组来说，他由两个有序的子数组构成，如果我们可以找到两个数组的分界线
* 那么我们就可以先判断 target 在哪个数组范围内，然后利用二分查找快速的查找出来。
*
*/
int search(int* nums, int numsSize, int target) {
	if (numsSize == 0) {
		return -1;
	}
	else {
		int smallestIndex = findSmallestIndex(nums, numsSize);
		if (smallestIndex == 0) {
			return binarySearch(nums, 0, numsSize - 1, target);
		}
		else {
			int firstBegin = 0;
			int firstEnd = smallestIndex - 1;
			int secondBegin = smallestIndex;
			int secondEnd = numsSize - 1;
			// 如果 target 在第一个有序数组的范围内，那么就在第一个数组中使用二分查找搜索
			if (target >= *(nums + firstBegin) && target <= *(nums + firstEnd)) {
				return binarySearch(nums, firstBegin, firstEnd, target);
			}
			// 同理，在第二个数组范围内，对第二个数组进行二分搜索
			else if (target >= *(nums + secondBegin) && target <= *(nums + secondEnd)) {
				return binarySearch(nums, secondBegin, secondEnd, target);
			}
			else {
				return -1;
			}
		}
	}
}

int main() {
	int arr[] = { 4,5,1,2,3 };
	int size = sizeof(arr) / sizeof(int);
	int target = 1;
	int r = search(arr, size, target);
	printf("r is: %d\n", r);
	system("pause");
	return 0;
}