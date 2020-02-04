# Question

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Answer

其实这就是两个链表直接相加即可，如果有进位，带入下次运算。代码如下：

```c
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
```







