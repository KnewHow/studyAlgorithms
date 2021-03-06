# 61. Rotate List

Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

每次将最后一个元素移动到头节点即可，不过有个规律，设链表的长度为n,若k为n的整数倍，则不需要任何操作，实际上我们需要执行的操作为`k%n`次，代码如下：

```c
#pragma once
#include <cstddef>
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    int getListSize(ListNode* head) {
        int size = 0;
        while (head != NULL) {
            size++;
            head = head->next;
        }
        return size;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        int size = getListSize(head);
        if (size <= 1) {
            return head;
        }
        else {
            int rk = k % size;
            for (int i = 0; i < rk; i++) {
                ListNode* p = head;
                ListNode* end = p->next;
                while (end->next != NULL) {
                    p = p->next;
                    end = p->next;
                }
                p->next = NULL;
                end->next = head;
                head = end;
            }
            return head;
        }
    }
    void printList(ListNode* head) {
        while (head != NULL) {
            cout << head->val << "->";
            head = head->next;
        }
        cout << "NULL" << endl;
    }
};
```



