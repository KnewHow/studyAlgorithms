#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include "hashtable.h"
#include "helper.h"



/**
* 判断 z 的值是否是 x 或者 y 本身
* @param nums 原数组
* @param size 数组大小
* @param xIndex x 的角标
* @param yIndex y 的角标
* @param z z的值
* @return 如果 z 的值是 x 或者 y 本身，返回 1，否则返回 0
*/
int isSelf(int* num, int size, int xIndex, int yIndex, int z) {
	for (int i = 0; i < size; i++) {
		// 不是本身
		if (num[i] == z && i != xIndex && i != yIndex) {
			return 0;
		}
	}
	// 是本身
	return 1;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 * 使用暴力法求解,双重循环确定 x 和 y, 然后二分查找来确定 z,
 * 但是很不幸，这个方法效率太低，运行超时
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
			if (index != -1) { // 找到了
				// 如果不是本身才做，否则表明 z 的值是 x 或者 y 的其中之一
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
* 获取小于等于0的元素并去重
* @param nums 有序数组
* @param size 数组大小
* @param newSize 新数组的长度，使用指针带回
* @return 返回一个去重且小于等于的新数组
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
* 两数之和解法,
* @param 给定数组
* @param size 数组大小
* @param target 目标数
* @param target 目标数的原始角标
* @param hashTable 存放结果的 hashTable
* @param numbers 将原数组进行 hash 打散的结果
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
* 上面的方法有点不怎么聪明，需要使用双重循环来确定 x, y，然后在确定 z,
* 我们再看看题目，既然要求我们找出三个数之和为0，那么肯定有一个数 >=0,我们分如下情况讨论
* 1.若三个数之中有一个数为0，则我们只需要找任意两数之和为0即可，转换为两数之和
* 2.若三个数均不为0，则必有一个负数，我们找数组中两数之和等于该负数的相反数，转换为两数之和
* 
* 因此算法思路如下：找出原数组中小于等于0的元素，然后去重，
* 找出原数组中是否有两个元素之和等于他们
*/
int** threeSumOpt(
	int* nums,
	int numsSize,
	int* returnSize,
	int** returnColumnSizes
) {
	// 存放结果的 hashTable
	PHashTable hashTable = initHashTable();
	// 将原数组复制一份并排序
	int* newNums = copyArray(nums, numsSize);
	quickSort(newNums, numsSize);
	// 存放原数组所有元素和角标的 hashTable
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