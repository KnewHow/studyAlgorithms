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
	Solution s;
	std::vector<int> nums = { 1,4,3,2,5,2 };
	int x = 3;
	ListNode* head = vectorToList(nums);
	ListNode* res = s.partition(head, 3);
	printList(res);
	std::cin.get();
	return 0;
}