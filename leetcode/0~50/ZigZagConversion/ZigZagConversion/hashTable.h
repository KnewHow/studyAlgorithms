#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

typedef struct Element {
	char c;
	struct Element* next;
} Element, * PElement;

typedef struct Head {
	PElement head;
	PElement tail;
} Head, *Phead;

Phead* init(int size) {
	Phead* hashTable = (Phead*)malloc(sizeof(Phead) * size);
	if (hashTable == NULL) {
		printf("init hashTable error: malloc failure");
		return NULL;
	}
	else {
		for (Phead* p = hashTable; p < hashTable + size; p++) {
			*p = NULL;
		}
		return hashTable;
	}
}

void put(Phead* hashTable, int index, char c) {
	Phead head = hashTable[index];
	if (head == NULL) {
		head = (Phead)malloc(sizeof(Head));
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = NULL;
		head->head = e;
		head->tail = e;
		hashTable[index] = head;
	}else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = NULL;
		head->tail->next = e;
		head->tail = e;
	}
}

char* toString(Phead* hashTable, int size, int row) {
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	char* p = str;
	for (int i = 0; i < row; i++) {
		Phead head = hashTable[i];
		if (head != NULL) {
			PElement temp = head->head;
			while (temp != NULL) {
				*p = temp->c;
				p++;
				temp = temp->next;
			}
		}
	}
	*p = '\0';
	return str;
}


