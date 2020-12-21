#pragma once
#include<limits>
#include<vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isValidBST2(TreeNode* root);
    /**
    * һ�����������������ж��Ƿ��Ƕ���������
    */
    bool help(TreeNode* root, long long lower, long long upper);

    bool isValidBST(TreeNode* root);

    void InOrderTraversal(TreeNode* root, std::vector<int>& res);

};