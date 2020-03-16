# Next Permutation

实现获取下一个排列的函数，算法需要将给定数字序列重新排列成**字典序**中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。

```
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

首先我们需要明白何谓**字典序**，可以参考百度百科[字典序](https://baike.baidu.com/item/字典序)。其实百度百科中已经给出了如何求下一个字典顺序的算法，代码如下：

```c
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
```

