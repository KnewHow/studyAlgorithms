#pragma once
#include<stdio.h>
#include<stdlib.h>
#define N 1024
#define STRING_SIZE 26

// ����ĳ���ַ����Ľṹ��
typedef struct Element {
	/** һ������Ϊ 26 �����飬
	* str[0]Ԫ�ش��� a ���ֵ�Ƶ�ʣ�str[1] ���� b  ���ֵ�Ƶ�� ... str[25] ���� z ���ֵ�Ƶ�� 
	*/
	int* str;
	int size; // Ԫ�ظ���
	int* indexs; // �ַ�����ԭ����ĽǱ�ļ���
	struct Element* next;
} Element, *PElement;

// hashTable �ṹ��
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
* �����ַ����� hashCode, ����������ַ�-97�ĺ���ΪhashCode
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
* ����������ַ�������Сд��ĸ��ɣ����������԰��ַ���ת��Ϊһ��26λ�����顣
* ����ÿ���ַ����ֶ��ٴ�
*/
int* getStrArray(char* str) {
	int* arr = (int*)malloc(sizeof(int) * STRING_SIZE);
	for (int i = 0; i < STRING_SIZE; i++) {
		*(arr + i) = 0;
	}
	while (*str != '\0') {
		char c = *str;
		// a ��Ӧ arr[0], b ��Ӧ arr[1],�Դ�����
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
* �Ƚ϶����Ƿ�Ϊͬһ�� str,����ֻ��Ҫ�Ƚ��ַ����ֵ�Ƶ���Ƿ���ͬ����
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
			if (isSameStr(p->str, strArray)) { // �ҵ���ͬ��
				p->indexs[p->size++] = index;
				return;
			}
			else { // û�ҵ���������
				p = p->next;
			}
		}
		free(strArray);
		// �����ն�û�ҵ���˵�����µ� str ����
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
* �� hashTable �еĽ����װΪ��Ŀ��Ҫ���ַ����Ķ�ά����
* @param hashTable �Ѿ�����õ� hashTable
* @param strs ԭ�ַ�������
* @param returnSize ��Ҫ���ض�λ���� row �Ĵ�С
* @param returnColumnSize ��Ҫ���ض�ά�����еĴ�С
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

