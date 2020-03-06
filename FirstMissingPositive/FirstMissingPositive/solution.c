#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

void quickSortR(int* arr, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = *(arr + begin);
		while (left < right) {
			while (left < right && *(arr + right) >= pivot) {
				right--;
			}

			while (left < right && *(arr + left) <= pivot) {
				left++;
			}
			swap(arr, left, right);
		}
		swap(arr, begin, left);
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

int firstMissingPositive(int* nums, int numsSize) {
	quickSort(nums, numsSize);
	int begin = 0;
	while (begin < numsSize) {
		if (*(nums + begin) < 1) {
			begin++;
		}
		else {
			break;
		}
	}
	if (begin == numsSize) { // 全部为负数
		return 1;
	}
	else {
		int counter = 1;
		for (int i = begin; i < numsSize; i++) {
			// 每次让 counter 自增，如果 arr[i] > counter，
			// 说明中间有个最小正整数被遗漏
			if (*(nums + i) == counter) {
				counter++;
			}
			else {
				if (*(nums + i) > counter) {
					return counter;
				}
				/*如果 出现 arr[i] < counter,
				表示 arr[i] 和 arr[i-1] 出现重复，
				此时我们保持counter 不变，i 自增 */
			}
		}
		/* 如果循环结束依旧没有返回，
		说明arr[begin] ~ arr[size-1] 为连续正整数，
		此时返回 arr[size-1] + 1 */
		return *(nums + numsSize - 1) + 1;
	}
}

/**
* 对于 n 个数来说，如果他是从 1~ n 的，说明他不缺失，如果他有任意一个数
* 超过了 n, 说明他在 1~n 之内，肯定有缺失，因此下面程序中的 max 最大值为 n
*/
int firstMissingPositive2(int* nums, int numsSize) {
	int max = INT_MIN;
	for (int i = 0; i < numsSize; i++) {
		if (*(nums + i) > max) {
			max = *(nums + i);
		}
	}

	// 如果最大值超过 n,则在 1 ~ n 之间肯定有间断点，我们不需要再去考虑比 n 大的数
	if (max > numsSize) {
		max = numsSize;
	}

	if (max < 1) { // 所有的数都是小于 1，直接返回1
		return 1;
	}
	else {
		// 使用一个数组，来标记 nums[i] - 1 的值 
		int* arr = (int*)malloc(sizeof(int) * max);
		for (int i = 0; i < max; i++) {
			*(arr + i) = 0;
		}
		for (int i = 0; i < numsSize; i++) {
			int value = *(nums + i);
			// 只考虑 1~n 之间的数
			if (value >= 1 && value <= numsSize) {
				// 对于出现 nums[i]-1 的标记为 1
				int index = value - 1;
				*(arr + index) = 1;
			}
		}
		for (int i = 0; i < max; i++) {
			// 表示 arr[j] - 1 = i 数没有出现，在 i+1 出现间断点
			if (*(arr + i) == 0) {
				return i+1;
			}
		}
		// 所有值都存在，返回 max + 1
		return max+1; 
	}
}

int main() {
	int nums[] = { 2147483647 };
	int size = sizeof(nums) / sizeof(int);
	int r = firstMissingPositive2(nums, size);
	printf("r is: %d\n", r);
	system("pause");
	return 0;
}