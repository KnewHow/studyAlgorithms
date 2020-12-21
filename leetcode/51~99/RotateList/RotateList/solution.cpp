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
