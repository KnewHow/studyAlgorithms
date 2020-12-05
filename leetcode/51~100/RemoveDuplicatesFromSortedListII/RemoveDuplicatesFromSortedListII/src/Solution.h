#pragma once
#include<unordered_set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
 
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head);
    ListNode* deleteDuplicates2(ListNode* head);
};