#include<stdlib.h>
#include<stdio.h>

int searchInsert(int* nums, int numsSize, int target) {
	int begin = 0;
	int end = numsSize - 1;
	int mid = (begin + end) / 2;
	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target == *(nums + mid)) {
			return mid;
		}
		else if (target < *(nums + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	// Ã»ÕÒµ½
	if (target < * (nums + mid)) {
		return mid;
	}
	else {
		return mid + 1;
	}
}

int main() {
	int nums[] = { 1,3 };
	int size = sizeof(nums) / sizeof(int);
	int target = 2;
	int index = searchInsert(nums, size, target);
	printf("index is:%d\n", index);
	system("pause");
	return 0;
}