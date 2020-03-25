# Question

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Answer

## 解法一：暴力法

我们可以直接对给定的数组进行暴力循环，找到 x + y + z = 0，不过该算法的时间复杂度较，为`O(n^3)`

定义一个 hashTable 来存储结果已经去重使用

```c
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1024

typedef struct Element {
	int* tuple; // 一维数组，
	int size; // 数组大小
	struct Element* next; // 指向下个元素的指针
} Element, *PElement;

// 获取一个数的绝对值
int absV(int a) {
	if (a >= 0) {
		return a;
	}
	else {
		return -a;
	}
}

/**
* 计算每个 Element 的 hashCode,这里使用数组中每个元素的绝对值相加
* 但是这样做在数值过大的情况下会导致 int 溢出，
* 后序可以优化为使用每个数字字符的 ASCII 相加，但我们先这样试试
* @param nums 数组
* @param size 数组 size
* @return 计算后的 hashCode
*/
int hashCode(int* nums, int size) {
	int* p = nums;
	int code = 0;
	while (p < nums + size) {
		code += absV(*p);
		p++;
	}
	return code;
}

PHashTable initHashTable() {
	PElement* tables = (PElement*)malloc(N * sizeof(PElement));
	PElement* p = tables;
	while (p < tables + N) {
		*p = NULL;
		p++;
	}
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	hashTable->size = 0;
	hashTable->tables = tables;
	return hashTable;
}

int isSame(PElement e, int* nums, int size) {
	int* p1 = e->tuple;
	int* p2 = nums;
	while (p1 < e->tuple + e->size && p2 < nums + size) {
		if (*p1 != *p2) {
			return 0;
		}
		p1++;
		p2++;
	}
	if (p1 == e->tuple + e->size && p2 == nums + size) { // 都遍历完成
		return 1;
	}
	else { // 有一个未遍历完成
		return 0;
	}
}

int exists(PHashTable hashTable, int* nums, int size) {
	int code = hashCode(nums, size);
	int index = code % N;
	PElement head = *(hashTable->tables + index);
	if (head == NULL) {
		return 0;
	}
	else {
		PElement p = head;
		while (p != NULL) {
			if (isSame(p, nums, size)) { // 如果相同，说明存在
				return 1;
			}
			else { // 否则比较下一个
				p = p->next;
			}
		}
		return 0; // 比完都没有相同，则不包含
	}
}

void put(PHashTable hashTable, int* nums, int size) {
	int code = hashCode(nums, size);
	int index = code % N;
	PElement head = *(hashTable->tables + index);
	if (head == NULL) { // 没有元素
		head = (PElement)malloc(sizeof(Element));
		head->size = size;
		head->tuple = nums;
		head->next = NULL;
		*(hashTable->tables + index) = head;
		hashTable->size++;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->size = size;
		e->tuple = nums;
		e->next = head;
		*(hashTable->tables + index) = e;
		hashTable->size++;
	}
}



// 将 hashTable 转换为二维数组
int** toArray(PHashTable hashTable) {
	int** arr = (int**)malloc(hashTable->size * sizeof(int*));
	int** p = arr;
	PElement* tables = hashTable->tables;
	for (int i = 0; i < N; i++) {
		PElement head = *(tables + i);
		if (head != NULL) {
			PElement q = head;
			while (q != NULL) {
				*p = q->tuple;
				p++;
				q = q->next;
			}
		}
	}
	return arr;
}
```

一些辅助函数

```c
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

void printArr(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", arr[i]);
		}
		else {
			printf("%d, ", arr[i]);
		}
		
	}
	printf(" ]\n");
}

void quickSortR(int* arr, int begin, int end) {
	if (end  > begin) { // 当数组元素大于 1 个的时候做
		int pivot = *(arr + begin);
		int left = begin;
		int right = end;
		while (left < right) {
			while (arr[right] >= pivot && left < right) {
				right--;
			}
			while (arr[left] <= pivot && left < right) {
				left++;
			}
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
		int temp = arr[begin];
		arr[begin] = arr[left];
		arr[left] = temp;
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, right + 1, end);
	}
}

/**
* 快速排序
* @param arr 给定数组
* @param size 数组大小
*/
void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

/**
* 二分查找
* @param arr 有序数组
* @param size 数组大小
* @param value 需要查找的数
* @return 如果找到该元素，返回该元素的角标，否则返回 -1
*/
int binarySearch(int* arr, int size, int value) {
	int begin = 0;
	int end = size - 1;
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (*(arr + mid) == value) {
			return mid;
		}
		else if (value > *(arr + mid)) {
			begin = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	// 没找到
	return -1; 
}

/**
* 将x,y,z三个数按照从小到大的顺序放入一个数组中
* @return 一个存放三个有序元素的数组
*/
int* toSortedArray(int x, int y, int z) {
	int* arr = (int*)malloc(sizeof(int) * 3);
	*(arr + 0) = x;
	*(arr + 1) = y;
	*(arr + 2) = z;
	quickSort(arr, 3);
	return arr;
}

/**
* 由原数组复制一个新的数组
*/
int* copyArray(int* nums, int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	int* p1 = arr;
	int* p2 = nums;
	while (p2 < nums + size) {
		*p1++ = *p2++;
	}
	return arr;
}
```

解决函数：

```c
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
```





## 解法二：利用两数之和来完成

还记得我们之前我们做过的两数之和吗，我们可以先确定一个数，然后在原数组中查找另一个数，但是这里有三个数，我们似乎无法根据一个数在线性的时间复杂度内查找另外两个数，但是由于结果是0，我们可以用点小技巧。

* 我们知道 0 + 任何数都为 0，首先我们查找数组中是否有0，如果有，则我们只需要找到两个数之和为0，即可，这样问题就变成了求两数之和，时间复杂度 `O(NLgN)`
* 当数组不含0时，我们知道，要想三个数相加为零，肯定得有一个负数，我们找出数组中所有的负数，然后在查找哪两个数之和等于它，问题又转换成两数之和，时间复杂度为`O(NLgn)`

通过上面的分析，我们知道我们先找该数组中小于等于0的数，然后在查找是否有两数之和等于他们的相反数。

对最后的结果需要去重，那如何去重呢？

我们可以将每个三元组按照从小到大的顺序排列，然后存入结果，每次插入前先比较是否重复，然后在插入，由于结果是有限次，这里的时间复杂度不会太大。当然我们可以使用一个 HashTable 来存储结果

一个用于查找原数组的数字的HashTable

```c
typedef struct Number {
	int value; // 数字的值
	int index; // 数字在原数组下的角标
	struct Number* next;
} Number, *PNumber;

// 存储数字和角标的 hashTable,和上面的类型
PNumber* initNumberHashTable() {
	PNumber* numbers = (PNumber*)malloc(sizeof(PNumber) * N);
	for (int i = 0; i < N; i++) {
		*(numbers + i) = NULL;
	}
	return numbers;
}

/**
* 往 hashTable 放入一个数
* @param numbers 哈希表
* @param value 数字的值
* @param index 数字在原数组的下标
*/
void putNumber(PNumber* numbers, int value, int index) {
	int code = absV(value);
	int pos = code % N;
	PNumber head = *(numbers + pos);
	if (head == NULL) {
		head = (PNumber)malloc(sizeof(Number));
		head->index = index;
		head->value = value;
		head->next = NULL;
		*(numbers + pos) = head;
	}
	else {
		PNumber n = (PNumber)malloc(sizeof(Number));
		n->index = index;
		n->value = value;
		n->next = head;
		*(numbers + pos) = n;
	}
}

/**
* 获取值为value,但是 index != index 的元素
* @params numbers 已经初始化的 hash 表
* @params value 需要查找的数值
* @params index 查找的值需要不等于当前的 index
* @params index2 查找不等于 index2 的角标，如果index ==-1,忽略
* @return 如果找到元素，返回对应的 PNumber，找不到返回 NULL
*/
PNumber get(
	PNumber* numbers, 
	int value,
	int index,
	int index2
) {
	int code = absV(value);
	int pos = code % 1024;
	PNumber head = numbers[pos];
	if (head == NULL) {
		return NULL;
	}
	else {
		PNumber p = head;
		while (p != NULL) {
			if (index2 == -1) {
				if (p->value == value && p->index != index) {
					return p;
				}
			}
			else {
				if (p->value == value 
					&& p->index != index 
					&& p->index != index2) {
					return p;
				}
			}
			p = p->next;
		}
		return NULL;
	}
}
```



```c
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
```

虽然我的代码有点复杂，执行起来还稍微慢了一点，但是思路还是很清晰的，时间复杂度为`O(knlgn),k为原数组中小于等于0且去重后的元素个数`，在极端情况下为`O(n^2)`,但是可以优化，比较去重后小于等于0和大于等于0的元素个数，去二者中最小的集合。