#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"helper.h"
#include"avltree.h"
#include "hashTable.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// 暴力法求解
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


// 先排序，在二分查找
int* twoSumWithSort(int* nums, int numsSize, int target, int* returnSize) {
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

// 使用 AVL 树进行查找
int* twoSumWithAVLTree(int* nums, int numsSize, int target, int* returnSize) {
	PTree root = NULL;
	// 将原始数组逐一插入 AVL 树
	for (int* p = nums; p < nums + numsSize; p++) {
		root = push(root, *p);
	}
	for (int* p = nums; p < nums + numsSize; p++) {
		int y = target - *p;
		PTree node = find(root, y); 
		// 没找到
		if (node == NULL) {
			continue;
		} else { // 找到了
			int value = node->value;
			for (int i = 0; i < numsSize; i++) {
				// 找了了并且该元素的和*p不是同一个元素
				if (nums[i] == value && i != (p - nums)) {
					int* r = (int*)malloc(2 * sizeof(int));
					if (r == NULL) {
						return NULL;
					}
					else {
						r[0] = (p - nums);
						r[1] = i;
						*returnSize = 2;
						return r;
					}
				} else {
					continue;
				}
			}
		}
	}
	return NULL;
}

// 使用 HashTabel 构建
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



int main() {
	int nums[] = { -3,4,3,90 };
	int target = 0;
	int returnSize = 0;
	int* r = twoSumWithHashTable(nums, sizeof(nums)/sizeof(int), target, &returnSize);
	for (int* p = r; p < r + returnSize; p++) {
		printf("index=%d\n", *p);
	}
	free(r);
	//PElement* table = NULL;
	// table = initTable();
	//for(int )
	// testPerformance();
	system("pause");
	return	0;
}