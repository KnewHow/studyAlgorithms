#include "Solution.h"

ListNode* Solution::reverseBetween(ListNode* head, int m, int n)
{
	if (head == nullptr) {
		return head;
	}
	ListNode* left = head;
	ListNode* leftPrevious = head;
	ListNode* right = head;
	ListNode* rightNext = head;
	for (int i = 1; i < m; i++) {
		leftPrevious = left;
		left = left->next;
	}
	for (int i = 1; i < n; i++) {
		right = right->next;
		rightNext = right->next;
	}
	if (left == right) {
		return head; // same node, do nothing
	}
	else if (left == nullptr) {
		return head;
	}
	else {
		ListNode* newHead = right;
		ListNode* tail = left;
		ListNode* temp = nullptr;
		while (left != right) {
			newHead->next = left;
			left = left->next;
			if (temp == nullptr) {
				temp = newHead->next;
			}
			else {
				newHead->next->next = temp;
				temp = newHead->next;
			}
		}
		tail->next = rightNext;
		if (m == 1) {
			return newHead;
		}
		else {
			leftPrevious->next = newHead;
			return head;
		}
	}
}
