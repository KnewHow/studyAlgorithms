#include<stdlib.h>
#include<stdio.h>


struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode* newHead = NULL;
	struct ListNode* p = head;
	// 指向 p 的前驱节点
	struct ListNode* pPrevious = NULL; 
	while (p != NULL) {
		if (p->next != NULL) { // p next 存在，进行交换
			struct ListNode* pNext = p->next;
			p->next = pNext->next;
			pNext->next = p;
			// 如果 p 的前驱不为 NULL,让其指向 pNext
			if (pPrevious != NULL) {
				pPrevious->next = pNext;
			}
			else { // 如果 pPrevious 为 NULL,表示交换的头两个节点，此时需要记住头结点
				newHead = pNext;
			}
			pPrevious = p;
			p = p->next;
		}
		else {
			break;
		}
	}
	if (newHead != NULL) {
		return newHead;
	}
	else {
		return head;
	}
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

void printList(struct ListNode* list) {
	while (list != NULL) {
		printf("%d->", list->val);
		list = list->next;
	}
	printf("end\n");
}

int main() {
	int arr[] = { 1 };
	int size = sizeof(arr) / sizeof(int);
	struct ListNode* list = arrayToList(arr, size);
	struct ListNode* r = swapPairs(list);
	printList(r);
	system("pause");
	return 0;
}