#include "Solution.h"

ListNode* Solution::partition(ListNode* head, int x)
{
	if (head == nullptr) {
		return nullptr;
	}
	else {
		std::vector<int> lessThan;
		std::vector<int> others;
		while (head != nullptr) {
			if (head->val < x) {
				lessThan.push_back(head->val);
			}
			else {
				others.push_back(head->val);
			}
			ListNode* temp = head;
			head = head->next;
			delete(temp);
		}
		
		head = nullptr;
		ListNode* p = head;
		for (int i = 0; i < lessThan.size(); i++) {
			if (head == nullptr) {
				head = new ListNode(lessThan[i]);
				p = head;
			}
			else {
				ListNode* node = new ListNode(lessThan[i]);
				p->next = node;
				p = node;
			}
		}

		for (int i = 0; i < others.size(); i++) {
			if (head == nullptr) {
				head = new ListNode(others[i]);
				p = head;
			}
			else {
				ListNode* node = new ListNode(others[i]);
				p->next = node;
				p = node;
			}
		}
		return head;
	}	
}
