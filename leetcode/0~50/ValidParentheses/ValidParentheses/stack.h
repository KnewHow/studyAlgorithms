#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

typedef struct Element {
	char c; // 存储（、[ 或者 {
	struct Element* next;
} Element, *PElement;

// 压栈
PElement put(PElement head, char c) {
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		head->c = c;
		head->next = NULL;
		return head;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = head;
		return e;
	}
}

// 弹栈
PElement pop(PElement head) {
	if (head != NULL) {
		return head->next;
	}
	else {
		return NULL;
	}
}

// 获取栈顶元素
PElement getPop(PElement head) {
	if (head != NULL) {
		return head;
	}
	else {
		return NULL;
	}
}