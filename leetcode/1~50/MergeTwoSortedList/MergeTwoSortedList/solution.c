#include<stdlib.h>
#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* mergeTwoLists(
	struct ListNode* l1, 
	struct ListNode* l2
) {
	if (l1 != NULL && l2 != NULL) {
		struct ListNode* p1 = l1;
		struct ListNode* p2 = l2;
		struct ListNode* head = NULL;
		struct ListNode* tail = head;
		if (p1->val < p2->val) {
			head = p1;
			tail = head;
			p1 = p1->next;
		}
		else {
			head = p2;
			tail = head;
			p2 = p2->next;
		}
		while (p1 != NULL && p2 != NULL) {
			if (p1->val < p2->val) {
				tail->next = p1;
				tail = p1;
				p1 = p1->next;
			}
			else {
				tail->next = p2;
				tail = p2;
				p2 = p2->next;
			}
		}
		while (p1 != NULL) {
			tail->next = p1;
			tail = p1;
			p1 = p1->next;
		}
		while (p2 != NULL) {
			tail->next = p2;
			tail = p2;
			p2 = p2->next;
		}
		return head;
	}
	else if (l1 == NULL) {
		return l2;
	}
	else {
		return l1;
	}
}

struct ListNode* initList(int* arr, int size) {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->val = *(arr + i);
			head->next = NULL;
			tail = head;
		}
		else {
			struct ListNode* e = (struct ListNode*)malloc(sizeof(struct ListNode));
			e->val = *(arr + i);
			e->next = NULL;
			tail->next = e;
			tail = e;
		}
	}
	return head;
}

void printList(struct ListNode* list) {
	while (list != NULL) {
		printf("%d->", list->val);
		list = list->next;
	}
	printf("end\n");
}

int main() {
	int arr1[] = { 1,2,4 };
	int size1 = sizeof(arr1) / sizeof(int);
	int arr2[] = { 1,3,4 };
	int size2 = sizeof(arr2) / sizeof(int);
	struct ListNode* l1 = initList(arr1,size1);
	struct ListNode* l2 = initList(arr2, size2);
	struct ListNode* r = mergeTwoLists(l1, l2);
	printList(r);
	system("pause");
	return 0;
}