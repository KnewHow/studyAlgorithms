#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include "base.h"

// 双休链表节点
typedef struct Element {
	char tag; // 匹配符，'-'代表全匹配，'*'代表重复一次或多次
	char c; // 需要匹配的字符，'.'表示任意字符
	int begin; // 匹配当前模式开始角标
	int end; // 匹配当前模式的结束角标(不包含)
	int isMatch; // 是否匹配， 0-没有匹配失败，1-匹配成功，其中 b* 重复 0 次也表示匹配成功
	int matchCount; // 匹配的数量，默认为 0，'-' 最多是 1，'*' 匹配 >= 0
	int status; // 匹配状态 0-未匹配 1-匹配中 2-匹配完成
	struct Element* next; // 下一个元素
	struct Element* previous; // 前一个元素
} Element, *PElement;

// 链表 head
typedef struct Head {
	PElement head; // 指向链表的首元素
	PElement tail; // 指向链表的尾元素
} Head, *PHead;

PElement initElement(char tag, char c) {
	PElement e = (PElement)malloc(sizeof(Element));
	e->tag = tag;
	e->c = c;
	e->isMatch = 0; // 默认匹配失败
	e->matchCount = 0; // 默认无匹配次数
	e->begin = 0; // 开始的角标默认为 0
	e->end = 0; // 终止角标默认为 0
	e->status = 0; // 未开始匹配
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
