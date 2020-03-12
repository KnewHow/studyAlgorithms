#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef struct Element {
	int value;
	struct Element* previous; // ָ��ǰ���ڵ�
	struct Element* next; // ָ���̽ڵ�
} Element, * PElement;

// ����
typedef struct Queue {
	PElement head; // ָ�������Ԫ��
	PElement tail; // ָ�����βԪ��
} Queue, * PQueue;

PQueue newQueue() {
	PQueue queue = (PQueue)malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void putLast(PQueue queue, int value) {
	PElement e = (PElement)malloc(sizeof(Element));
	e->value = value;
	e->next = NULL;
	e->previous = NULL;
	if (queue->head == NULL) {
		queue->head = e;
		queue->tail = e;
	}
	else {
		queue->tail->next = e;
		e->previous = queue->tail;
		queue->tail = e;
	}
}

void removeLast(PQueue queue) {
	if (queue != NULL && queue->tail != NULL) {
		// ����������������Ԫ��
		if (queue->tail->previous != NULL) {
			PElement e = queue->tail;
			queue->tail = queue->tail->previous;
			free(e);
		}
		else { // ������ֻ��һ��Ԫ��
			PElement e = queue->tail;
			free(e);
			queue->head = NULL;
			queue->tail = NULL;
		}
	}
}