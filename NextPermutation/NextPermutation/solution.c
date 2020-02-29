#include<stdio.h>
#include<stdlib.h>

void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

void nextPermutation(int* nums, int numsSize) {
	if (numsSize > 1) {
		// 找出 nums 中 nums[index] < nums[nextIndex]
		int index = -1;
		int nextIndex = -1;
		for (int i = 0; i < numsSize - 1; i++) {
			if (*(nums + i) < *(nums + i + 1)) {
				index = i;
				nextIndex = i + 1;
			}
		}
		// 当找到 index 比较靠后的反序时，我们不能确定要交换 indexNext 顺序
		// 我们还需要比较 indexNext 后面是否有 比 index 大且比 indexNext 更小或者相等的数
		// 表示有下一个序列
		if (index != -1 && nextIndex != -1) {
			int i = nextIndex + 1;
			int min = *(nums + nextIndex);
			while (i < numsSize) {
				if (*(nums + index) < *(nums + i) && *(nums + i) <= min) {
					min = *(nums + i);
					nextIndex = i;
				}
				i++;
			}
			swap(nums, index, nextIndex);
			// 在交换位置后，需要将 index+1 ~ size 的元素反转
			int mid = (index + 1 + numsSize) / 2;
			for (int j = index+1; j < mid; j++) {
				swap(nums, j, numsSize -j + index);
			}
		}
		else { // 否则表示 nums 已为全部的逆序序列，直接反转
			int mid = numsSize / 2;
			for (int i = 0; i < mid; i++) {
				swap(nums, i, numsSize - 1 - i);
			}
		}
	}
}

printfArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d,", *(arr + i));
		}
	}
	printf(" ]\n");
}

int main() {
	int nums[] = { 2,3,1,3,3 };
	int size = sizeof(nums) / sizeof(int);
	nextPermutation(nums, size);
	printfArray(nums, size);
	system("pause");
	return 0;
}