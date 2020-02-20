#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define N 1024

typedef struct Element {
	int* arr;  // �洢������
	int size; // ÿ������Ĵ�С
	struct Element* next;
} Element, *PElement;

typedef struct HashTable {
	PElement* tables; // �洢����Ԫ�ص�����
	int size; // hash ��Ĵ�С
} HashTable, *PHashTable;

PHashTable initHashTable() {
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	PElement* tables = (PElement*)malloc(sizeof(PElement) * N);
	for (PElement* p = tables; p < tables + N; p++) {
		*p = NULL;
	}
	hashTable->size = 0;
	hashTable->tables = tables;
	return hashTable;
}

int hashCode(int* arr, int size) {
	int sum = 0;
	for (int* p = arr; p < arr + size; p++) {
		sum += abs(*p); // ������Ԫ�صľ���ֵ�����Ϊ hashCode
	}
	return sum;
}

int isSame(int* arr1, int size1, int* arr2, int size2) {
	if (size1 != size2) {
		return 0;
	}
	else {
		int* p1 = arr1;
		int* p2 = arr2;
		while (p1 < arr1 + size1 && p2 < arr2 + size2) {
			if (*p1 != *p2) {
				return 0;
			}
			p1++;
			p2++;
		}
		return 1;
	}
}

/**
* �ж�����Ԫ���Ƿ��ظ�
*/
int exists(PHashTable hashTable, int* arr, int size) {
	int code = hashCode(arr, size);
	int pos = code % N;
	PElement head = *(hashTable->tables + pos);
	if (head == NULL) {
		return 0;
	}
	else {
		PElement p = head;
		while (p != NULL) {
			if (isSame(p->arr, p->size, arr, size)) {
				return 1;
			}
			p = p->next;
		}
		return 0;
	}
}

void put(PHashTable hashTable, int* arr, int size) {
	// ������ʱ��ִ�в������
	//printf("put:\t");
	// printArr(arr, size);
	if (!exists(hashTable, arr, size)) {
		int code = hashCode(arr, size);
		int pos = code % N;
		PElement head = *(hashTable->tables + pos);
		if (head == NULL) {
			head = (PElement)malloc(sizeof(Element));
			head->arr = arr;
			head->size = size;
			head->next = NULL;
			*(hashTable->tables + pos) = head;
		}
		else {
			PElement e = (PElement)malloc(sizeof(Element));
			e->arr = arr;
			e->size = size;
			e->next = head;
			*(hashTable->tables + pos) = e;
		}
		hashTable->size++;

	}
}

int** toArray(PHashTable hashTable) {
	int** arr = (int**)malloc(hashTable->size * sizeof(int*));
	int** p = arr;
	for (int i = 0; i < N; i++) {
		PElement head = *(hashTable->tables + i);
		while (head != NULL) {
			*p = head->arr;
			head = head->next;
			p++;
		}
	}
	return arr;
}

