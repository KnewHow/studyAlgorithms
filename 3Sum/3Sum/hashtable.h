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

typedef struct Number {
	int value; // 数字的值
	int index; // 数字在原数组下的角标
	struct Number* next;
} Number, *PNumber;

// HashTable
typedef struct HashTable {
	int size; // hash table 的 size
	PElement* tables; // 具体的 hash 桶，实际上就是个数组
} HashTable, *PHashTable;

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
