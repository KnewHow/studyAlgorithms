#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 128

// 链表元素节点
typedef struct Element {
	int index; // 元素的角标
	struct Element* next;
} Element, *PElement;

typedef struct Head {
	PElement head; // 链表的首元素
	PElement tail; // 链表的尾元素
} Head, *PHead;

// hashTable 的首元素不存储具体的数据，存储两个指针，一个指向链表的首元素，一个指向链表尾元素
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
		// 将后来的元素(角标较大)的元素插入链表尾部
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