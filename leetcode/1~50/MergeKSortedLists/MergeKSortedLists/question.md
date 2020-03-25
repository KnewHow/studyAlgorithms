#  sMerge k Sorted Lists

Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-k-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

我们可以每次取`n`中最小的元素，让他插入到结果链表中，然后继续比较下一组，如果其中一个链表为空，跳过之。

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    struct ListNode* head = NULL;
	struct ListNode* tail = head;
	while (1) {
		// 当前链表头中最小元素的角标，初始化为 -1
		int minIndex = -1;
		for (int i = 0; i < listsSize; i++) {
			if (*(lists + i) != NULL) {
				if (minIndex == -1) { // 未初始化
					minIndex = i;
				}
				else { // 为初始化，作比较
					if ((*(lists + i))->val < (*(lists + minIndex))->val) {
						minIndex = i;
					}
				}
			}
		}
		if (minIndex == -1) { // 表示全部为 NULL,结束循环
			break;
		}
		else {
			if (head == NULL) {
				head = *(lists + minIndex);
				tail = head;
				*(lists + minIndex) = (*(lists + minIndex))->next;
			}
			else {
				tail->next = *(lists + minIndex);
				tail = *(lists + minIndex);
				*(lists + minIndex) = (*(lists + minIndex))->next;
			}
		}
	}
	return head;
}
```

这样的算法执行效率似乎不高，通过测试需要**572 ms**，战胜8.59 %的人，时间复杂度为：`KN`，`k`为链表个数。



看了官方的题解，似乎先把链表元素重新组成一个数组，然后排序，再组成一个新的链表更快些，我们可以来试试。

```c
void quickSortR(int* arr, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = *(arr + left);
		while (left < right) {
			while (left < right && *(arr + right) >= pivot) {
				right--;
			}
			while (left < right && *(arr + left) <= pivot) {
				left++;
			}

			int temp = *(arr + left);
			*(arr + left) = *(arr + right);
			*(arr + right) = temp;
		}
		int temp = *(arr + left);
		*(arr + left) = *(arr + begin);
		*(arr + begin) = temp;
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	int* arr = (int*)malloc(sizeof(int) * 102400);
	int size = 0;
	// 将链表的元素重新组成数组
	for (int i = 0; i < listsSize; i++) {
		struct ListNode* p = *(lists + i);
		while (p != NULL) {
			*(arr + size) = p->val;
			size++;
			p = p->next;
		}
	}
	// 对数组进行快速排序
	quickSort(arr, size);
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	// 将排序后的元素组成新的链表
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->val = *(arr + i);
			head->next = NULL;
			tail = head;
		}
		else {
			struct ListNode* e = (struct ListNode*)malloc(sizeof(struct ListNode));
			e->val = *(arr + i);
			e->next = NULL;
			tail->next = e;
			tail = e;
		}
	}
	return head;
}
```

使用下面的代码果然快了很多，通过测试用例用例**20ms**左右。但是这样似乎根本没有用上题目给的有序链表，时间复制度为`NlogN`