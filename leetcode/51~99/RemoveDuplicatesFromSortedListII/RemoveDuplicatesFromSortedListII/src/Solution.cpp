#include "Solution.h"

ListNode* Solution::deleteDuplicates(ListNode* head)
{
	if (head == nullptr) {
		return head;
	}
	else {
		std::unordered_set<int> duplicates;
		int currentElement = head->val;
		int currentElementAppearTimes = 1;
		ListNode* p = head -> next;
		// find duplicate elements
		while (p != nullptr) {
			if (currentElement == p->val) {
				currentElementAppearTimes++;
			}
			else {
				if (currentElementAppearTimes > 1) {
					duplicates.insert(currentElement);
				} 
				currentElement = p->val;
				currentElementAppearTimes = 1;
			}
			p = p->next;
		}

		// last element relicates
		if (currentElementAppearTimes > 1) {
			duplicates.insert(currentElement);
		}

		ListNode* previous = head;
		p = head->next;
		while (p != nullptr) {
			if (duplicates.find(p->val) != duplicates.end()) { // find duplicate elements
				// delete p
				p = p->next;
				previous->next = p;
			}
			else {
				previous = p;
				p = p->next;
			}
		}

		if (duplicates.find(head->val) != duplicates.end()) { // head has duplicates
			head = head->next;
		}
		return head;

	}
	
	
}

ListNode* Solution::deleteDuplicates2(ListNode* head)
{
	if (head == nullptr) {
		return head;
	}
	else if(head != nullptr && head->next == nullptr) { // Only One Element
		return head;
	}
	else {
		bool isDeleteHead = head->val == head->next->val;
		ListNode* leftPrevious = head;
		ListNode* left = head->next;
		ListNode* right = head->next;
		int currentElement = left->val;
		int currentElementAppearTimes = 1;
		right = right->next;
		while (right != nullptr) {
			if (right->val == currentElement) {
				++currentElementAppearTimes;
				right = right->next;
			}
			else {
				if (currentElementAppearTimes > 1) {
					// delete left ~ right
					leftPrevious->next = right;
					left = right;
					currentElement = left->val;
					currentElementAppearTimes = 1;
					right = right->next;
				}
				else {
					leftPrevious = left;
					left = right;
					currentElement = left->val;
					currentElementAppearTimes = 1;
					right = right->next;
				}
			}
		}

		// duplicates appear last
		if (currentElementAppearTimes > 1) {
			leftPrevious->next = right;
		}

		// delete head
		if (isDeleteHead) { // if there only two front element duplicates, the program above don't delete them, so delete them here by hand
			if (head->next != nullptr && head->val == head->next->val) {
				head = head->next->next;
			}
			else {
				head = head->next;
			}
		}
		return head;
	}
}
