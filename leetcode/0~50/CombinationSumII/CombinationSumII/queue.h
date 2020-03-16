#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef struct Element {
	int value;
	struct Element* previous; // 指向前驱节点
	struct Element* next; // 指向后继节点
} Element, * PElement;

// 队列
typedef struct Queue {
	PElement head; // 指向队列首元素
	PElement tail; // 指向队列尾元素
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
		// 队列中至少有两个元素
		if (queue->tail->previous != NULL) {
			PElement e = queue->tail;
			queue->tail = queue->tail->previous;
			free(e);
		}
		else { // 队列中只有一个元素
			PElement e = queue->tail;
			free(e);
			queue->head = NULL;
			queue->tail = NULL;
		}
	}
}