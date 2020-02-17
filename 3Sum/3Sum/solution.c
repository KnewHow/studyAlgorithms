#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include "hashtable.h"
#include "helper.h"



/**
* �ж� z ��ֵ�Ƿ��� x ���� y ����
* @param nums ԭ����
* @param size �����С
* @param xIndex x �ĽǱ�
* @param yIndex y �ĽǱ�
* @param z z��ֵ
* @return ��� z ��ֵ�� x ���� y �������� 1�����򷵻� 0
*/
int isSelf(int* num, int size, int xIndex, int yIndex, int z) {
	for (int i = 0; i < size; i++) {
		// ���Ǳ���
		if (num[i] == z && i != xIndex && i != yIndex) {
			return 0;
		}
	}
	// �Ǳ���
	return 1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 * ʹ�ñ��������,˫��ѭ��ȷ�� x �� y, Ȼ����ֲ�����ȷ�� z,
 * ���Ǻܲ��ң��������Ч��̫�ͣ����г�ʱ
 */
int** threeSumFource(
	int* nums, 
	int numsSize, 
	int* returnSize, 
	int** returnColumnSizes
) {
	PHashTable hashTable = initHashTable();
	int *newNums = copyArray(nums, numsSize);
	quickSort(newNums, numsSize);
	for (int x = 0; x < numsSize; x++) {
		for (int y = x + 1; y < numsSize; y++) {
			int z = 0 - nums[x] - nums[y];
			int index = binarySearch(newNums, numsSize, z);
			if (index != -1) { // �ҵ���
				// ������Ǳ��������������� z ��ֵ�� x ���� y ������֮һ
				if (!isSelf(nums, numsSize, x, y, z)) {
					int* arr = toSortedArray(nums[x], nums[y], newNums[index]);
					int r = exists(hashTable, arr, 3);
					if (!r) {
						put(hashTable, arr, 3);
					}
				}
			}
		}
	}
	int** r = toArray(hashTable);
	*returnSize = hashTable->size;
	int *columns = (int*)malloc(sizeof(int) * hashTable->size);
	for (int i = 0; i < hashTable->size; i++) {
		*(columns + i) = 3;
	}
	*returnColumnSizes = columns;
	return r;
}

/**
* ��ȡС�ڵ���0��Ԫ�ز�ȥ��
* @param nums ��������
* @param size �����С
* @param newSize ������ĳ��ȣ�ʹ��ָ�����
* @return ����һ��ȥ����С�ڵ��ڵ�������
*/
int* obtainLessZero(int* nums, int size, int *newSize) {
	int* arr = (int*)malloc(sizeof(int) * size);
	int ns = 0;
	int previous = 999999;
	for (int i = 0; i < size; i++) {
		if (nums[i] != previous) {
			previous = nums[i];
			arr[ns++] = nums[i];
		}
	}
	*newSize = ns;
	return arr;
}

/**
* ����֮�ͽⷨ,
* @param ��������
* @param size �����С
* @param target Ŀ����
* @param target Ŀ������ԭʼ�Ǳ�
* @param hashTable ��Ž���� hashTable
* @param numbers ��ԭ������� hash ��ɢ�Ľ��
*/
void twoSum(
	int* nums, 
	int size, 
	int target, 
	int targetIndex,
	PHashTable hashTable,
	PNumber* numbers
) {
	for (int i = 0; i < size; i++) {
		if (i != targetIndex) {
			int x = nums[i];
			int y = target - x;
			PNumber r = get(numbers, y, targetIndex, i);
			if (r != NULL) {
				int* arr = toSortedArray(-target, x, y);
				int r = exists(hashTable, arr, 3);
				if (!r) {
					put(hashTable, arr, 3);
				}
			}
		}
	}
}

/**
* ����ķ����е㲻��ô��������Ҫʹ��˫��ѭ����ȷ�� x, y��Ȼ����ȷ�� z,
* �����ٿ�����Ŀ����ȻҪ�������ҳ�������֮��Ϊ0����ô�϶���һ���� >=0,���Ƿ������������
* 1.��������֮����һ����Ϊ0��������ֻ��Ҫ����������֮��Ϊ0���ɣ�ת��Ϊ����֮��
* 2.������������Ϊ0�������һ������������������������֮�͵��ڸø������෴����ת��Ϊ����֮��
* 
* ����㷨˼·���£��ҳ�ԭ������С�ڵ���0��Ԫ�أ�Ȼ��ȥ�أ�
* �ҳ�ԭ�������Ƿ�������Ԫ��֮�͵�������
*/
int** threeSumOpt(
	int* nums,
	int numsSize,
	int* returnSize,
	int** returnColumnSizes
) {
	// ��Ž���� hashTable
	PHashTable hashTable = initHashTable();
	// ��ԭ���鸴��һ�ݲ�����
	int* newNums = copyArray(nums, numsSize);
	quickSort(newNums, numsSize);
	// ���ԭ��������Ԫ�غͽǱ�� hashTable
	PNumber* hashNumbers = initNumberHashTable();
	for (int i = 0; i < numsSize; i++) {
		putNumber(hashNumbers, nums[i], i);
	}
	int newSize = 0;
	int* baseArr = obtainLessZero(newNums, numsSize, &newSize);
	for (int i = 0; i < newSize; i++) {
		PNumber nu = get(hashNumbers, baseArr[i], -1, -1);
		twoSum(nums,numsSize,(0 - nu->value),nu->index,hashTable,hashNumbers);
	}
	int** r = toArray(hashTable);
	*returnSize = hashTable->size;
	int* columns = (int*)malloc(sizeof(int) * hashTable->size);
	for (int i = 0; i < hashTable->size; i++) {
		*(columns + i) = 3;
	}
	*returnColumnSizes = columns;
	return r;
}



int main() {
	int nums[] = { 0,0 };
	int size = sizeof(nums) / sizeof(int);
	int returnSize = 0;
	int *columSize = NULL;
	int **r = threeSumOpt(nums, size, &returnSize, &columSize);
	int** p = r;
	printf("{\n");
	while (p < r + returnSize) {
		int size = *(columSize + (p - r));
		printArr(*p, size);
		p++;
	}
	printf("}\n");
	system("pause");
	return 0;
}