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
	// ����1ʱ��Ϊ����
	if (k == 1) {
		return head;
	}
	else {
		// begin ��ǰһ���ڵ�
		struct ListNode* beginPrevious = NULL;
		struct ListNode* begin = head;
		struct ListNode* p = head;
		struct ListNode* end = NULL;
		// �µ������ͷ
		struct ListNode* newHead = NULL;
		// ��ǰ�ڵ�Ϊ��һ���ڵ㣬���� length ��ʼΪ 1
		int length = 1;
		while (p != NULL) {
			if (length == k) { // �ҵ��˴� begin �� end �� k ���ڵ�
				end = p;
				p = p->next;
				struct ListNode* tempHead = begin;
				struct ListNode* tempTail = begin;
				begin = begin->next;
				// ��ѭ������ʱ�� begin �պõ��� p,�������¿�ʼ
				while (begin <= end && begin != NULL) {
					struct ListNode* next = begin;
					begin = begin->next;
					next->next = tempHead;
					tempHead = next;
				}
				// length ����Ϊ1
				length = 1;
				// ���µ�βָ��ָ�� p
				tempTail->next = p;
				// ���֮ǰ�� begin ͷָ��δ���壬���¾ֲ������βָ��Ϊ tempTail

				if (beginPrevious == NULL) {
					beginPrevious = tempTail;
				}
				// ������֮ǰ�� begin ǰָ��ָ���µ� head,Ȼ�����¾ֲ������βָ��Ϊ tempTail
				else {
					beginPrevious->next = tempHead;
					beginPrevious = tempTail;
				}
				// ��� newHead δ���壬��ʾ�ǵ�һ������ת���� newHead ��Ϊ���ε� tempHead
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