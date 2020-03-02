#include<stdlib.h>
#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
	if (head != NULL) {
		struct ListNode* newHead = head;
		struct ListNode* tail = head;
		struct ListNode* p = head->next;
		while (p != NULL) {
			struct ListNode* temp = p;
			p = p->next;
			temp->next = newHead;
			newHead = temp;
		}
		tail->next = NULL;
		return newHead;
	}
	else {
		return head;
	}
}

void printList(struct ListNode* head) {
	while (head != NULL) {
		printf("%d->", head->val);
		head = head->next;
	}
	printf("end\n");
}

struct ListNode* arrayToList(int* arr, int size) {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->next = NULL;
			head->val = *(arr + i);
			tail = head;
		}
		else {
			struct ListNode* e = (struct ListNode*)malloc(sizeof(struct ListNode));
			e->next = NULL;
			e->val = *(arr + i);
			tail->next = e;
			tail = e;
		}
	}
	return head;
}

int main() {
	int arr[] = { 1,2,3,4,5 };
	int size = sizeof(arr) / sizeof(int);
	struct ListNode* l1 = arrayToList(arr, size);
	printList(l1);
	struct ListNode* l2 = reverseList(l1);
	printList(l2);
	system("pause");
	return 0;
}