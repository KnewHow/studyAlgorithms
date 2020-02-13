#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include "base.h"

// ˫������ڵ�
typedef struct Element {
	char tag; // ƥ�����'-'����ȫƥ�䣬'*'�����ظ�һ�λ���
	char c; // ��Ҫƥ����ַ���'.'��ʾ�����ַ�
	int begin; // ƥ�䵱ǰģʽ��ʼ�Ǳ�
	int end; // ƥ�䵱ǰģʽ�Ľ����Ǳ�(������)
	int isMatch; // �Ƿ�ƥ�䣬 0-û��ƥ��ʧ�ܣ�1-ƥ��ɹ������� b* �ظ� 0 ��Ҳ��ʾƥ��ɹ�
	int matchCount; // ƥ���������Ĭ��Ϊ 0��'-' ����� 1��'*' ƥ�� >= 0
	int status; // ƥ��״̬ 0-δƥ�� 1-ƥ���� 2-ƥ�����
	struct Element* next; // ��һ��Ԫ��
	struct Element* previous; // ǰһ��Ԫ��
} Element, *PElement;

// ���� head
typedef struct Head {
	PElement head; // ָ���������Ԫ��
	PElement tail; // ָ�������βԪ��
} Head, *PHead;

PElement initElement(char tag, char c) {
	PElement e = (PElement)malloc(sizeof(Element));
	e->tag = tag;
	e->c = c;
	e->isMatch = 0; // Ĭ��ƥ��ʧ��
	e->matchCount = 0; // Ĭ����ƥ�����
	e->begin = 0; // ��ʼ�ĽǱ�Ĭ��Ϊ 0
	e->end = 0; // ��ֹ�Ǳ�Ĭ��Ϊ 0
	e->status = 0; // δ��ʼƥ��
	e->next = NULL;
	return e;
}

PHead put(PHead head, char tag, char c) {
	if (head == NULL) {
		head = (PHead)malloc(sizeof(Head));
		if (head == NULL) {
			printf("[put] malloc head failure\n");
			return NULL;
		}
		PElement e = initElement(tag, c);
		e->previous = NULL;
		head->head = e;
		head->tail = e;
		return head;
	}
	else {
		PElement e = initElement(tag, c);
		e->previous = head->tail;
		head->tail->next = e;
		head->tail = e;
		return head;
	}	
}


void freeList(PHead head) {
	if(head != NULL) {
		PElement h = head->head;
		while (h != NULL)
		{
			PElement temp = h;
			h = h->next;
			free(temp);
			temp = h;
		}
	}
}

void printList(PHead head) {
	if (head == NULL) {
		printf("the list is empty\n");
	}
	else {
		PElement h = head->head;
		while (h != NULL) {
			printf("tag:%c, c:%c, begin:%d,end:%d, isMatch:%d, matchCount:%d,status:%d\n",
				h->tag, h->c,h->begin,h->end,h->isMatch, h->matchCount,h->status);
			h = h->next;
		}
	}
}
