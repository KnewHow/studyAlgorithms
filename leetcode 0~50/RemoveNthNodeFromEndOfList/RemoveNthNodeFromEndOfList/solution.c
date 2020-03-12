#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	// 统计链表的 size
	int size = 0;
	struct ListNode* p = head;
	while (p != NULL) {
		size++;
		p = p->next;
	}
	if (size == 0) {
		return head;
	}
	if (size == 1) { // 如果只有一个元素，默认移除本身，返回 NULL
		return NULL;
	}
	if (n == size) { // 如果 n==size,表示移出首元素，则返回 head->next
		return head->next;
	}
	else { // 正常情况下按照下面的算法
		int m = size - n + 1;
		int counter = 0;
		struct ListNode* p = head;
		while (counter < m-2) {
			p = p->next;
			counter++;
		}
		if (p->next != NULL) {
			p->next = p->next->next;
		}
		else { // 否则表明是该链表就一个元素，返回NULL
			return NULL;
		}
		
	}
	return head;
}

void printList(struct ListNode* head) {
	while (head != NULL) {
		printf("%d->", head->val);
		head = head->next;
	}
	printf("null\n");
}

int main() {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	for (int i = 1; i <= 2; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->next = NULL;
			head->val = i;
			tail = head;
		}
		else {
			struct ListNode*  node = (struct ListNode*)malloc(sizeof(struct ListNode));
			node->next = NULL;
			node->val = i;
			tail->next = node;
			tail = node;
		}
	}
	printList(head);
	head = removeNthFromEnd(head, 2);
	printList(head);
	system("pause");
	return 0;
}