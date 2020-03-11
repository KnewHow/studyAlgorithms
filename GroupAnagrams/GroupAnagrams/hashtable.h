#pragma once
#include<stdio.h>
#include<stdlib.h>
#define N 1024
#define STRING_SIZE 26

// 具体某个字符串的结构体
typedef struct Element {
	/** 一个长度为 26 的数组，
	* str[0]元素代表 a 出现的频率，str[1] 代表 b  出现的频率 ... str[25] 代表 z 出现的频率 
	*/
	int* str;
	int size; // 元素个数
	int* indexs; // 字符串在原数组的角标的集合
	struct Element* next;
} Element, *PElement;

// hashTable 结构体
typedef struct HashTable {
	int size;
	PElement* tables;
}HashTable, *PHashTable;


PHashTable initHashTable() {
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	PElement* tables = (PElement*)malloc(sizeof(PElement) * N);
	for (int i = 0; i < N; i++) {
		*(tables + i) = NULL;
	}
	hashTable->size = 0;
	hashTable->tables = tables;
	return hashTable;
}

/**
* 计算字符串的 hashCode, 这里把所有字符-97的和最为hashCode
*/
int hashCode(char* str) {
	int code = 0;
	while (*str != '\0') {
		char c = *str;
		code += (c - 97);
		str++;
	}
	return code;
}

/**
* 由于这里的字符串都是小写字母组成，因此这里可以把字符串转换为一个26位的数组。
* 代表每个字符出现多少次
*/
int* getStrArray(char* str) {
	int* arr = (int*)malloc(sizeof(int) * STRING_SIZE);
	for (int i = 0; i < STRING_SIZE; i++) {
		*(arr + i) = 0;
	}
	while (*str != '\0') {
		char c = *str;
		// a 对应 arr[0], b 对应 arr[1],以此类推
		int index = c - 97;
		*(arr + index) = *(arr + index) + 1;
		str++;
	}
	return arr;
}

PElement createElement(char* str, int index) {
	PElement p = (PElement)malloc(sizeof(Element));
	int* strArray = getStrArray(str);
	int* indexs = (int*)malloc(sizeof(int) * N);
	int size = 0;
	*(indexs + size++) = index;
	p->indexs = indexs;
	p->size = size;
	p->str = strArray;
	p->next = NULL;
	return p;
}

/**
* 比较二者是否为同一个 str,这里只需要比较字符出现的频率是否相同即可
*/
int isSameStr(int* str1, int* str2) {
	for (int i = 0; i < STRING_SIZE; i++) {
		if (*(str1 + i) != *(str2 + i)) {
			return 0;
		}
	}
	return 1;
}

void push(PHashTable hashTable, char* str, int index) {
	int code = hashCode(str);
	int pos = code % N;
	PElement* tables = hashTable->tables;
	PElement head = *(tables + pos);
	if (head == NULL) {
		PElement p = createElement(str, index);
		head = p;
		*(tables + pos) = head;
		hashTable->size++;
	}
	else {
		PElement p = head;
		int* strArray = getStrArray(str);
		while (p != NULL) {
			if (isSameStr(p->str, strArray)) { // 找到相同的
				p->indexs[p->size++] = index;
				return;
			}
			else { // 没找到，继续找
				p = p->next;
			}
		}
		free(strArray);
		// 到最终都没找到，说明有新的 str 产生
		p = createElement(str, index);
		p->next = head;
		*(tables + pos) = p;
		hashTable->size++;
	}
}

void freeHashTable(PHashTable hashTable) {
	PElement* tables = hashTable->tables;
	for (int i = 0; i < N; i++) {
		PElement head = *(tables + i);
		while (head != NULL) {
			PElement p = head;
			head = head->next;
			free(p->str);
			free(p->indexs);
			free(p);
		}
	}
	free(hashTable);
}

/**
* 将 hashTable 中的结果组装为题目需要的字符串的二维数组
* @param hashTable 已经计算好的 hashTable
* @param strs 原字符串数组
* @param returnSize 需要返回二位数组 row 的大小
* @param returnColumnSize 需要返回二维数组列的大小
*/
char*** toGroup(PHashTable hashTable, char **strs, int* returnSize, int** returnColumnSizes) {
	char*** r = (char***)malloc(sizeof(char**) * hashTable->size);
	*returnSize = hashTable->size;
	*(returnColumnSizes) = (int*)malloc(sizeof(int) * hashTable->size);
	int size = 0;
	PElement* tables = hashTable->tables;
	for (int i = 0; i < N; i++) {
		PElement head = *(tables + i);
		while (head != NULL) {
			*(*(returnColumnSizes)+size) = head->size;
			char** strArray = (char**)malloc(sizeof(char*) * head->size);
			int* indexs = head->indexs;
			for (int j = 0; j < head->size; j++) {
				*(strArray + j) = *(strs + *(indexs + j));
			}
			*(r + size) = strArray;
			size++;
			head = head->next;
		}
	}
	freeHashTable(hashTable);
	return r;
}


void testGetStrArray() {
	char* s1 = "duh";
	char* s2 = "ill";
	int* arr1 = getStrArray(s1);
	int* arr2 = getStrArray(s2);
	for (int i = 0; i < STRING_SIZE; i++) {
		printf("%d ", *(arr1 + i));
	}
	printf("\n");
	for (int i = 0; i < STRING_SIZE; i++) {
		printf("%d ", *(arr2 + i));
	}
	printf("\n");
}

