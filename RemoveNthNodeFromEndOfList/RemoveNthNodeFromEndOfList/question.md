# Question

Given a linked list, remove the n-th node from the end of list and return its head.

Example:

Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:

Given n will always be valid.

Follow up:

Could you do this in one pass?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

对于一个长度为`size`的链表来说，倒数第`n`个元素元素就是顺数第`size-n+1`个元素，然后让链表删除他即可。

```c
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
	// 统计链表的 size
	int size = 0;
	struct ListNode* p = head;
	while (p != NULL) {
		size++;
		p = p->next;
	}
	if (size == 0) {
		return head;
	}
	if (size == 1) { // 如果只有一个元素，默认移除本身，返回 NULL
		return NULL;
	}
	if (n == size) { // 如果 n==size,表示移出首元素，则返回 head->next
		return head->next;
	}
	else { // 正常情况下按照下面的算法
		int m = size - n + 1;
		int counter = 0;
		struct ListNode* p = head;
		while (counter < m-2) {
			p = p->next;
			counter++;
		}
		if (p->next != NULL) {
			p->next = p->next->next;
		}
		else { // 否则表明是该链表就一个元素，返回NULL
			return NULL;
		}
		
	}
	return head;
}

void printList(struct ListNode* head) {
	while (head != NULL) {
		printf("%d->", head->val);
		head = head->next;
	}
	printf("null\n");
}

int main() {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	for (int i = 1; i <= 2; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->next = NULL;
			head->val = i;
			tail = head;
		}
		else {
			struct ListNode*  node = (struct ListNode*)malloc(sizeof(struct ListNode));
			node->next = NULL;
			node->val = i;
			tail->next = node;
			tail = node;
		}
	}
	printList(head);
	head = removeNthFromEnd(head, 2);
	printList(head);
	system("pause");
	return 0;
}
```

至于题目说的遍历一次，我们可以在第一次计算长度的时候，用一个数组来存储链表中的每个元素，然后等统计完 `size`后，根据角标来定位需要产生的元素，这样遍历一次即可，是以空间换时间的思路