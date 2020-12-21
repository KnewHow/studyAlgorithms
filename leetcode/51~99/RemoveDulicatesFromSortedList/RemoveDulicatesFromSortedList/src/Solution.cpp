#include "Solution.h"

ListNode* Solution::deleteDuplicates(ListNode* head)
{
	if (head == nullptr) {
		return head;
	}
	else if (head->next == nullptr) {
		return head;
	}
	else {
		ListNode* previous = head;
		ListNode* p = head->next;
		while (p != nullptr) {
			if (previous->val == p->val) {
				// delete p
				p = p->next;
				previous->next = p;
			}
			else {
				previous = p;
				p = p->next;
			}
		}
		return head;

	}
}
