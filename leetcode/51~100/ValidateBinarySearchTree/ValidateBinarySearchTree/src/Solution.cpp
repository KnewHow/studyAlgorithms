#include "Solution.h"

bool Solution::isValidBST2(TreeNode* root)
{
	return help(root, LONG_MIN, LONG_MAX);
}

bool Solution::help(TreeNode* root, long long lower, long long upper)
{
	if (root == nullptr) {
		return true;
	} 

	if (root->val >= upper || root->val <= lower) {
		return false;
	}

	return help(root->left, lower, root->val) && help(root->right, root->val, upper);
}

bool Solution::isValidBST(TreeNode* root)
{
	std::vector<int> res;
	InOrderTraversal(root, res);
	if (res.empty()) {
		return true;
	}
	else {
		for (int i = 0; i < res.size() - 1; i++) {
			if (res[i] >= res[i + 1]) {
				return false;
			}
		}
	}
	return true;
}

void Solution::InOrderTraversal(TreeNode* root, std::vector<int>& res) 
{
	if (root == nullptr) {
		return;
	}
	else {
		InOrderTraversal(root->left,res);
		res.push_back(root->val);
		InOrderTraversal(root->right,res);
	}
}
