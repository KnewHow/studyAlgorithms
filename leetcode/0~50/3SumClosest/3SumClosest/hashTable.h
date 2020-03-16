#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1024

typedef struct Element {
	int value;
	int index;
	struct Element* next;
} Element, *PElement;

PElement* initHashTable() {
	PElement* hashTable = (PElement*)malloc(sizeof(PElement) * N);
	PElement* p = hashTable;
	while (p < hashTable + N) {
		*p = NULL;
		p++;
	}
	return hashTable;
}

int hashCode(int value) {
	// ��ֵ�ľ���ֵ��Ϊ hashcode
	return abs(value);
}

void put(PElement* hashTable, int value, int index) {
	int pos = hashCode(value) % N;
	PElement head = *(hashTable + pos);
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		head->index = index;
		head->value = value;
		head->next = NULL;
		*(hashTable + pos) = head;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->index = index;
		e->value = value;
		e->next = head;
		*(hashTable + pos) = e;
	}
}

/**
* �ڹ�ϣ���в��� value ������index ������ xIndex �� yIndex Ԫ��
* @param hashTable �Ѿ���ʼ���� hashTable
* @param value 
* @param xIndex x��ԭ����ĽǱ�
* @param yIndex y��ԭ����ĽǱ�
* @return �ҵ����ض�ӦԪ��ָ�룬���򷵻� NULL
*/
PElement get(PElement* hashTable, int value, int xIndex, int yIndex) {
	int pos = hashCode(value) % N;
	PElement head = *(hashTable + pos);
	if (head == NULL) {
		return NULL;
	}
	else {
		PElement p = head;
		while (p != NULL) {
			if (p->value == value && p->index != xIndex && p->index != yIndex) {
				return p;
			}
			p = p->next;
		}
		return NULL;
	}
}
