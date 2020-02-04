# question
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

Tips1:
A really brute force way would be to search for all possible pairs of numbers but that would be too slow. Again, 
it's best to try out brute force solutions for just for completeness. It is from these brute force solutions that 
you can come up with optimizations.

Tips2：
So, if we fix one of the numbers, say
x
, we have to scan the entire array to find the next number
y
which is
value - x
where value is the input parameter. Can we change our array somehow so that this search becomes faster?

Tip3:
The second train of thought is, without changing the array, can we use additional space somehow? Like maybe a hash map
to speed up the search?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# answer
关于如何求解，提示已经说的很明显了，我们遍历一次给定的数组，当遍历到第`i`个元素的时候，我们需要查找`target-nums[i]`的位置。那么这道题目就变成如果查找数组中一个元素的问题。

## 解法一：暴力查找

我们当然可以先遍历一遍数组，当遍历到第`i`个元素的时候，我们使用另一个`for`循环来逐个遍历原数组，找出`target-nums[i]` ,但是这样算法效率不高，时间复杂度为O(N^2)

```c
int* twoSumFource(int* nums, int numsSize, int target, int* returnSize) {
	for (int* x = nums; x < nums + numsSize; x++) {
		int y = target - *x;
		for (int* p = nums; p < nums + numsSize; p++) {
			if ((x - nums) == (p - nums)) { // 由于题目要求两个数字不能是同一个数字
				continue;
			}
			else
			{
				if (*p == y) {
					int* r = (int*)malloc(2 * sizeof(int));
					if (r != NULL) {
						r[0] = (x - nums);
						r[1] = (p - nums);
						*returnSize = 2;
						return r;
					}
					else
					{
						return NULL;
					}

				}
			}
		}
	}
	return NULL;
}
```



## 解法二：先排序，然后然后使用二分查找

题目要求我们返回元素的原数组角标，乍一看，我们似乎不能对原数组进行排序，因为排序会改变数组的位置。但是我们可以复制一份原数组，然后进行排序。在新排好序的数组中使用二分查找排查找`target-num[i]`,然后在原数组中查找该元素的原始角标。

生成一个新的对象数组需要`O(N)`的时间，使用快速排序算法排序一个数组需要`O(NlgN)`，遍历一个数组然后然后使用二分查找查找数组元素需要`O(N * lnN)`,所以总的时间复杂度为：`O(NlgN)`

```c
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
   int* p = NULL;
	p = copyArray(nums, numsSize);
	if (p != NULL) {
		quickSort(p, 0, numsSize - 1);
		for (int* x = nums; x < nums + numsSize; x++) {
			int y = target - *x;
			int index = binarySearch(p, numsSize, y);
			if (index != -1) { // 找到了
				int value = p[index];
				// 遍历原数组，查找原角标
				for (int i = 0; i < numsSize; i++) {
					// 题目要求两个数字的角标不能重复，因此二分查找的元素的角标不能与x的角标一样
					if (nums[i] == value && i != (x - nums)) {
						// 成功找到元素
						free(p);
						int* r = (int*)malloc(2 * sizeof(int));
						if (r != NULL) {
							r[0] = (x - nums);
							r[1] = i;
							*returnSize = 2;
							return r;
						}
					}
				}
			}
		}
		free(p);
		return NULL;
	}
	else
	{
		return NULL;
	}
}
```

## 解法三：构建二叉搜索树

既然是查找，除了先排序，然后使用二分查找以外，我们还可以直接构建一棵AVL(红黑树)树来查找。构建AVL树的时间复杂度为O(NlgN)，遍历查找的时间复杂度为：O(NlgN)，总的时间复杂度为：O(Nlgn)



## 解法四：利用散列表（Hash Table）实现近似O(n)的算法

既然是查找，我们可以使用散列表，这样每次查找的效率就位O(1),那么遍历查找的时间复杂度就位O(n).那我们如何构建散列表呢？对于学Java的小伙伴来说，`HashMap`就是一个天然的散列表，而对于学`C`的同学来说，可能就得去网上查查案例，自己写了，但是，既然是学算法，自己写一个又如何呢。

```c
#pragma once
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define PRIME 1024

typedef struct Element {
	int value; // 值
	int index; // 在原数组的角标
	struct Element* next;
} Element, *PElement;

// 初始化 hashTable
PElement* initTable() {
	PElement* table = (PElement*)malloc(PRIME * sizeof(PElement));
	if (table == NULL) {
		printf("[initTable] malloc memory failure");
		return (PElement*)NULL;
	}
	else {
		for (int i = 0; i < PRIME; i++) {
			table[i] = NULL;
		}
		return table;
	}
}

// 获取元素的 hash index,对于负数取其相反数
int getPos(int value) {
	int pos = value % PRIME;
	if (pos < 0) {
		pos = pos * -1;
	}
	return pos;
}

// 往 hashTable 插入元素
PElement* put(PElement *table,int value, int index) {
	if (table == NULL) {
		table = initTable();
	}
	int pos = getPos(value);
	PElement head = table[pos];
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		if (head == NULL) {
			printf("[push-malloc-head] failure\n");
		}
		else {
			head->index = index;
			head->value = value;
			head->next = NULL;
			table[pos] = head;
		}
		
	} else {
		PElement temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		PElement node = (PElement)malloc(sizeof(Element));
		if (node == NULL) {
			printf("[push-malloc-node] failure\n");
		}
		else {
			node->value = value;
			node->index = index;
			node->next = NULL;
			temp->next = node;
		}

	}
	return table;
}

// 查询值==value 且角标 != index 的值
PElement query(PElement* table, int value, int index) {
	if (table == NULL) {
		return NULL;
	}
	else {
		int pos = getPos(value);
		PElement head = table[pos];
		if (head == NULL) {
			return NULL;
		}
		else {
			PElement temp = head;
			while (temp != NULL) {
				// 找值和value 相当，但是 index 不等的元素
				if (temp->value == value && temp->index != index) {
					return temp;
				}
				else {
					temp = temp->next;
				}
			}
			return NULL;
		}
	}
}

int* twoSumWithHashTable(
	int* nums, 
	int numsSize, 
	int target, 
	int* returnSize
) {
	PElement* table = NULL;
	for (int i = 0; i < numsSize; i++) {
		table = put(table, nums[i], i);
	}
	for (int i = 0; i < numsSize; i++) {
		int y = target - nums[i];
		PElement e = query(table, y, i);
		// 找到了
		if (e != NULL) {
			int* r = (int*)malloc(2 * sizeof(int));
			if (r == NULL) {
				return NULL;
			}
			else {
				r[0] = i;
				r[1] = e->index;
				*returnSize = 2;
				return r;
			}
		}
	}
	return NULL;
}
```

