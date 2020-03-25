#include"question.h"
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>


struct ListNode* addTwoNumbers(
	struct ListNode* l1, 
	struct ListNode* l2
) {
	struct ListNode* h1 = l1;
	struct ListNode* h2 = l2;
	int carray = 0;
	struct ListNode* head = NULL;
	struct ListNode* temp = NULL;
	while (h1 != NULL || h2 != NULL) {
		int a = 0;
		if (h1 != NULL) {
			a = h1->val;
			h1 = h1->next;
		}
		int b = 0;
		if (h2 != NULL) {
			b = h2->val;
			h2 = h2->next;
		}
		int r = a + b + carray;
		// 计算进位
		if (r >= 10) {
			carray = 1;
		}
		else {
			carray = 0;
		}
		int val = r % 10;
		if (head != NULL) {
			struct ListNode*  node = (struct ListNode*) malloc(sizeof(struct ListNode));
			node->val = val;
			node->next = NULL;
			temp->next = node;
			temp = node;
		}
		else {
			head = (struct ListNode*) malloc(sizeof(struct ListNode));
			head->val = val;
			head->next = NULL;
			temp = head;
		}
	}
	// 最后还有一位进位
	if (carray == 1) {
		struct ListNode* node = (struct ListNode*) malloc(sizeof(struct ListNode));
		node->val = carray;
		node->next = NULL;
		temp->next = node;
		temp = node;
	}
	return head;
}

// 测试
void addTwoNumbersWithFourceSpec() {
	int arr1[] = {2,4,3};
	int arr2[] = { 5,6,4 };
	struct ListNode* l1 = genList(arr1, sizeof(arr1) / sizeof(int));
	struct ListNode* l2 = genList(arr2, sizeof(arr2) / sizeof(int));
	// printList(l1);
	struct ListNode* r = addTwoNumbersWithFource(l1, l2);
	printList(r);
}




int main() {
	addTwoNumbersWithFourceSpec();
	system("pause");
	return 0;
}