#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"helper.h"
#include"avltree.h"
#include "hashTable.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// ���������
int* twoSumFource(int* nums, int numsSize, int target, int* returnSize) {
	for (int* x = nums; x < nums + numsSize; x++) {
		int y = target - *x;
		for (int* p = nums; p < nums + numsSize; p++) {
			if ((x - nums) == (p - nums)) { // ������ĿҪ���������ֲ�����ͬһ������
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


// �������ڶ��ֲ���
int* twoSumWithSort(int* nums, int numsSize, int target, int* returnSize) {
	int* p = NULL;
	p = copyArray(nums, numsSize);
	if (p != NULL) {
		quickSort(p, 0, numsSize - 1);
		for (int* x = nums; x < nums + numsSize; x++) {
			int y = target - *x;
			int index = binarySearch(p, numsSize, y);
			if (index != -1) { // �ҵ���
				int value = p[index];
				// ����ԭ���飬����ԭ�Ǳ�
				for (int i = 0; i < numsSize; i++) {
					// ��ĿҪ���������ֵĽǱ겻���ظ�����˶��ֲ��ҵ�Ԫ�صĽǱ겻����x�ĽǱ�һ��
					if (nums[i] == value && i != (x - nums)) {
						// �ɹ��ҵ�Ԫ��
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

// ʹ�� AVL �����в���
int* twoSumWithAVLTree(int* nums, int numsSize, int target, int* returnSize) {
	PTree root = NULL;
	// ��ԭʼ������һ���� AVL ��
	for (int* p = nums; p < nums + numsSize; p++) {
		root = push(root, *p);
	}
	for (int* p = nums; p < nums + numsSize; p++) {
		int y = target - *p;
		PTree node = find(root, y); 
		// û�ҵ�
		if (node == NULL) {
			continue;
		} else { // �ҵ���
			int value = node->value;
			for (int i = 0; i < numsSize; i++) {
				// �����˲��Ҹ�Ԫ�صĺ�*p����ͬһ��Ԫ��
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

// ʹ�� HashTabel ����
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
		// �ҵ���
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