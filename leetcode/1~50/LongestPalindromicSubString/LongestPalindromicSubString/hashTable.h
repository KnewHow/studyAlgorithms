#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 128

// ����Ԫ�ؽڵ�
typedef struct Element {
	int index; // Ԫ�صĽǱ�
	struct Element* next;
} Element, *PElement;

typedef struct Head {
	PElement head; // �������Ԫ��
	PElement tail; // �����βԪ��
} Head, *PHead;

// hashTable ����Ԫ�ز��洢��������ݣ��洢����ָ�룬һ��ָ���������Ԫ�أ�һ��ָ������βԪ��
PHead* init() {
	PHead* hashTable = (PHead*)malloc(N * sizeof(Head));
	if (hashTable == NULL) {
		printf("[init-hashTable] error\n");
		return NULL;
	}
	else {
		for (PHead* p = hashTable; p < hashTable + N; p++) {
			*p = NULL;
		}
		return hashTable;
	}
}

void put(PHead* hashTable, char c, int index) {
	int pos = c;
	PHead head = hashTable[pos];
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Head));
		PElement element = (PElement)malloc(sizeof(Element));
		element->index = index;
		element->next = NULL;
		head->head = element;
		head->tail = element;
		hashTable[pos] = head;
	}
	else {
		PElement element = (PElement)malloc(sizeof(Element));
		element->index = index;
		element->next = NULL;
		// ��������Ԫ��(�Ǳ�ϴ�)��Ԫ�ز�������β��
		head->tail->next = element;
		head->tail = element;
	}
}

PHead get(PHead* hashTable, char c) {
	int index = c;
	return hashTable[index];
}

int isExists(PElement* hashTable, char c) {
	int index = c;
	if (hashTable[index] == NULL) {
		return 0;
	}
	else {
		return 1;
	}
}