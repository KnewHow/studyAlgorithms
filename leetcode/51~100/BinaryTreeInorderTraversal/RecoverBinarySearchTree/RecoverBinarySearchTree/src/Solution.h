#pragma once
#include<vector>
#include<algorithm>

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
    void recoverTree(TreeNode* root);
    void doRecover(TreeNode* root, const int x, const int y, int counter);
    std::pair<int, int> findSwapNode(const std::vector<int> InOrderValues);
    void InOrderTraversal(TreeNode* root, std::vector<int>& InOrderValues);
};