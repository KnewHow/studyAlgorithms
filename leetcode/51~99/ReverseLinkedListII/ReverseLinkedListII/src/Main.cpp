#include<vector>
#include<iostream>
#include "Solution.h"

void printList(ListNode* head) {
	while (head != nullptr) {
		std::cout << head->val << "->";
		head = head->next;
	}
	std::cout << std::endl;
}

ListNode* vectorToList(std::vector<int> nums) {
	ListNode* head = new ListNode(nums[0]);
	ListNode* p = head;
	for (int i = 1; i < nums.size(); i++) {
		ListNode* n = new ListNode(nums[i]);
		p->next = n;
		p = n;
	}
	p->next = nullptr;
	return head;
}

int main() {
	std::vector<int> nums = { 1,2,3,4,5 };
	ListNode* head = vectorToList(nums);
	Solution s;
	int m = 2, n = 4;
	ListNode* newHead = s.reverseBetween(head, m, n);
	printList(newHead);
	std::cin.get();
	return 0;
}