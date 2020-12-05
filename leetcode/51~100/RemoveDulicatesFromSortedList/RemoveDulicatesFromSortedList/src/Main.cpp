#include<iostream>
#include<vector>
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
	std::vector<int> v = { 1,1,2,3,3 };
	Solution s;
	ListNode* head = s.deleteDuplicates(vectorToList(v));
	printList(head);
	std::cin.get();
	return 0;
}