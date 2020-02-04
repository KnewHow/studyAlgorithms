#pragma once
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define PRIME 1024

typedef struct Element {
	int value; // 值
	int index; // 在原数组的角标
	struct Element* next;
} Element, *PElement;

// 初始化 hashTable
PElement* initTable() {
	PElement* table = (PElement*)malloc(PRIME * sizeof(PElement));
	if (table == NULL) {
		printf("[initTable] malloc memory failure");
		return (PElement*)NULL;
	}
	else {
		for (int i = 0; i < PRIME; i++) {
			table[i] = NULL;
		}
		return table;
	}
}

// 获取元素的 hash index,对于负数取其相反数
int getPos(int value) {
	int pos = value % PRIME;
	if (pos < 0) {
		pos = pos * -1;
	}
	return pos;
}

// 往 hashTable 插入元素
PElement* put(PElement *table,int value, int index) {
	if (table == NULL) {
		table = initTable();
	}
	int pos = getPos(value);
	PElement head = table[pos];
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		if (head == NULL) {
			printf("[push-malloc-head] failure\n");
		}
		else {
			head->index = index;
			head->value = value;
			head->next = NULL;
			table[pos] = head;
		}
		
	} else {
		PElement temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		PElement node = (PElement)malloc(sizeof(Element));
		if (node == NULL) {
			printf("[push-malloc-node] failure\n");
		}
		else {
			node->value = value;
			node->index = index;
			node->next = NULL;
			temp->next = node;
		}

	}
	return table;
}

// 查询值==value 且角标 != index 的值
PElement query(PElement* table, int value, int index) {
	if (table == NULL) {
		return NULL;
	}
	else {
		int pos = getPos(value);
		PElement head = table[pos];
		if (head == NULL) {
			return NULL;
		}
		else {
			PElement temp = head;
			while (temp != NULL) {
				// 找值和value 相当，但是 index 不等的元素
				if (temp->value == value && temp->index != index) {
					return temp;
				}
				else {
					temp = temp->next;
				}
			}
			return NULL;
		}
	}
}