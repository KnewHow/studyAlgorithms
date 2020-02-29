#pragma once
#include<stdlib.h>
#include<malloc.h>

typedef struct Element {
	int index; // 存储 ( 对应的角标
	struct Element* next;
} Element, *PElement;

PElement push(PElement head, int index) {
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		head->next = NULL;
		head->index = index;
		return head;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->index = index;
		e->next = head;
		return e;
	}
}

PElement pop(PElement head) {
	if (head == NULL) {
		return NULL;
	}
	else {
		head = head->next;
	}
}

int isEmpty(PElement head) {
	if (head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

PElement getPop(PElement head) {
	if (head == NULL) {
		return NULL;
	}
	else {
		return head;
	}
}
