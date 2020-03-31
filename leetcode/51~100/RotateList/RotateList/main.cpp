#include<iostream>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	ListNode head = ListNode(1);
	ListNode tail = head;
	for (int i = 2; i <= 5; i++) {
		ListNode node = ListNode(i);
		tail.next = &node;
		tail = node;
	}
	s.printList(&head);
	int k = 4;
	ListNode *newHead = s.rotateRight(&head, k);
	s.printList(newHead);
	cout << "please any key to go on..." << endl;
	cin.get();
	return 0;
}