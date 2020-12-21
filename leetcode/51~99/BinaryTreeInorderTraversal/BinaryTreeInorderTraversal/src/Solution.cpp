#include "Solution.h"

std::vector<int> Solution::inorderTraversal(TreeNode* root)
{
	std::vector<int> res;
	doInorderRecursive(root, res);
	return res;
}

void Solution::doInorderRecursive(TreeNode* root, std::vector<int>& res)
{
	if (root == nullptr) {
		return;
	}
	else {
		doInorderRecursive(root->left, res);
		res.push_back(root->val);
		doInorderRecursive(root->right, res);
	}
}
