#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

 // Definition for singly-linked list.
struct ListNode {
      int val;
      struct ListNode *next;
  };

//将数组转换为链表，从第一个元素开始依次链接
struct ListNode* genList(int* arr, int size) {
	struct ListNode* head = NULL;
	struct ListNode* temp = NULL;
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*) malloc(sizeof(struct ListNode));
			head->val = arr[i];
			head->next = NULL;
			temp = head;
		}
		else {
			struct ListNode* node = (struct ListNode*) malloc(sizeof(struct ListNode));
			node->val = arr[i];
			node->next = NULL;
			temp->next = node;
			temp = node;
		}
	}
	return head;
}


 void printList(struct ListNode* head) {
	  if (head != NULL) {
		  printf("%d-> ", head->val);
		  printList(head->next);
	  }
	  else {
		  printf("null\n");
	  }
  }
 
