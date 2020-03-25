#include<stdlib.h>
#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

void printList(struct ListNode* list) {
	while (list != NULL) {
		printf("%d->", list->val);
		list = list->next;
	}
	printf("end\n");
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
	// 等于1时，为自身
	if (k == 1) {
		return head;
	}
	else {
		// begin 的前一个节点
		struct ListNode* beginPrevious = NULL;
		struct ListNode* begin = head;
		struct ListNode* p = head;
		struct ListNode* end = NULL;
		// 新的链表表头
		struct ListNode* newHead = NULL;
		// 当前节点为第一个节点，所有 length 初始为 1
		int length = 1;
		while (p != NULL) {
			if (length == k) { // 找到了从 begin 到 end 的 k 个节点
				end = p;
				p = p->next;
				struct ListNode* tempHead = begin;
				struct ListNode* tempTail = begin;
				begin = begin->next;
				// 当循环结束时， begin 刚好等于 p,正好重新开始
				while (begin <= end && begin != NULL) {
					struct ListNode* next = begin;
					begin = begin->next;
					next->next = tempHead;
					tempHead = next;
				}
				// length 重置为1
				length = 1;
				// 让新的尾指针指向 p
				tempTail->next = p;
				// 如果之前的 begin 头指针未定义，让新局部链表的尾指针为 tempTail

				if (beginPrevious == NULL) {
					beginPrevious = tempTail;
				}
				// 否则，让之前的 begin 前指针指向新的 head,然后让新局部链表的尾指针为 tempTail
				else {
					beginPrevious->next = tempHead;
					beginPrevious = tempTail;
				}
				// 如果 newHead 未定义，表示是第一次做反转，将 newHead 置为本次的 tempHead
				if (newHead == NULL) {
					newHead = tempHead;
				}
			}
			else {
				p = p->next;
				length++;
			}
		}
		if (newHead != NULL) {
			return newHead;
		}
		else {
			return head;
		}
	}
}


struct ListNode* arrayToList(int* arr, int size) {
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
	struct ListNode* list = arrayToList(arr, size);
	int k = 5;
	struct ListNode* newList = reverseKGroup(list, k);
	printList(newList);
	system("pause");
	return 0;
} 