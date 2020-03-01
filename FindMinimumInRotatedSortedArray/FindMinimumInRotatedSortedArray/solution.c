#include<stdlib.h>
#include<stdio.h>

/**
* 在 nums 中存在两个有序的数组 s1,s2, 在 s1,s2 中，都有 s[i] < s[i+1]
* 那么如果存在 j 使得 nums[j] >= nums[j+1],则 j 为 nums 的分界点，
* 且 j 为最大元素角标， j+1 为最小元素角标。
* 我们当然可以遍历一遍数组，找到 nums[j] >= nums[j+1]，但是这样的时间复杂度为 O(N)
* 能不能更快一点呢？
* 
* 我们可以利用二分搜索的思想。设 pivot = (begin + end) / 2;
* 如果 nums[pivot] >= nums[pivot + 1] 那么 pivot 就为分界点，否则我们继续比较
* nums[pivot] > nums[begin]? 如果大于，说明我们还在第一个有序的数组内，我们应该去右边找
* 让 begin = pivot(要知道 pivot 是不能舍弃的，因为它可能就是分界点，如 [5,4,1,2,3]),
* 否则说明我们已经到了第二个有序数组，应该往左半边找让 end = pivot
*/
int findMin(int* nums, int numsSize) {
	int begin = 0;
	int end = numsSize - 1;
	if (*(nums + begin) <= *(nums + end)) {
		return *(nums + 0);
	}
	else {
		while (begin <= end) {
			int pivot = (begin + end) / 2;
			if (*(nums + pivot) >= *(nums + pivot + 1)) {
				return *(nums + pivot + 1);
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

int main() {
	int arr[] = { 3,4,5,1,2 };
	int size = sizeof(arr) / sizeof(int);
	int min = findMin(arr, size);
	printf("min is:%d\n", min);
	system("pause");
	return 0;
}