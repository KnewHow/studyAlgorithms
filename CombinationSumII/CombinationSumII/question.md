# Combination Sum II

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

Each number in candidates may only be used once in the combination.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
Example 1:

```
Input: candidates = [10,1,2,7,6,1,5], target = 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
```

Example 2:

```
Input: candidates = [2,5,2,1,2], target = 5,
A solution set is:
[
  [1,2,2],
  [5]
]
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

和之前题目的方法应该类似，只是需要考虑如何去重的问题。

* 之前递归调用 solve 的时候，由于每个元素只能使用 1 次，所以 `i` 变成 `i+1`
* 在 begin 循环的地方，进行去重。



具体的代码如下：

```c
#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef struct Element {
	int value;
	struct Element* previous; // 指向前驱节点
	struct Element* next; // 指向后继节点
} Element, *PElement;

// 队列
typedef struct Queue {
	PElement head; // 指向队列首元素
	PElement tail; // 指向队列尾元素
} Queue, *PQueue;

PQueue newQueue() {
	PQueue queue = (PQueue)malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void putLast(PQueue queue, int value) {
	PElement e = (PElement)malloc(sizeof(Element));
	e->value = value;
	e->next = NULL;
	e->previous = NULL;
	if (queue->head == NULL) {
		queue->head = e;
		queue->tail = e;
	}
	else {
		queue->tail->next = e;
		e->previous = queue->tail;
		queue->tail = e;
	}
}

void removeLast(PQueue queue) {
	if (queue != NULL && queue->tail != NULL) {
		// 队列中至少有两个元素
		if (queue->tail->previous != NULL) {
			PElement e = queue->tail;
			queue->tail = queue->tail->previous;
			free(e);
		}
		else { // 队列中只有一个元素
			PElement e = queue->tail;
			free(e);
			queue->head = NULL;
			queue->tail = NULL;
		}
	}
}


#define MAX_SIZE 1000

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

int* toArray(PQueue queue, int *size) {
	int* arr = (int*)malloc(sizeof(int) * MAX_SIZE);
	*size = 0;
	PElement p = queue->head;
	while (p != NULL) {
		*(arr + *size) = p->value;
		*size = *size + 1;
		p = p->next;
	}
	return arr;
}

/**
* 递归的计算所有的数字
* @param candidates 已排序好的待选数组
* @param candidatesSize 数组大小
* @param target 目标数字
* @param begin 每次从 candidates 的 begin 下标开始
* @param returnSize 最终返回结果数组是 size 地址
* @param returnColumnSize 每个集合数组的大小
* @param res 存着最终结果集的二维数组
* @param queue 存储中间结果的队列
*/
void solve(
	int* candidates,
	int candidatesSize,
	int target,
	int begin,
	int* returnSize,
	int* returnColumnSizes,
	int** res,
	PQueue queue
) {
	if (target == 0) {
		int size = 0;
		*(res + *returnSize) = toArray(queue, &size);
		*(returnColumnSizes + *returnSize) = size;
		*returnSize = *returnSize + 1;
	}
	else {
		int previous = -1;
		for (int i = begin; i < candidatesSize; i++) {
			// 由于原数组已排好序，而且元素都为正数，这里可以这样去重
			if (*(candidates + i) != previous) {
				previous = *(candidates + i);
				// 如果 target - candidates[i] < 0,则后面更大是数更不可能，结束循环
				if (target - *(candidates + i) < 0) {
					break;
				}
				int value = *(candidates + i);
				putLast(queue, *(candidates + i));
				solve(
					candidates,
					candidatesSize,
					target - value,
					// 由于每个元素最多只能使用一次，因此 i+1
					i + 1,
					returnSize,
					returnColumnSizes,
					res,
					queue
				);
				removeLast(queue);
			}
			
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(
	int* candidates, 
	int candidatesSize, 
	int target, 
	int* returnSize, 
	int** returnColumnSizes) {
	PQueue queue = newQueue();
	int** res = (int**)malloc(sizeof(int*) * MAX_SIZE);
	*returnSize = 0;
	*returnColumnSizes = (int*)malloc(sizeof(int) * MAX_SIZE);
	quickSort(candidates, candidatesSize);
	solve(candidates, 
		candidatesSize, 
		target, 
		0, 
		returnSize, 
		*returnColumnSizes, 
		res, 
		queue
	);
	return res;
}
```

