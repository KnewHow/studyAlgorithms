#include "Solution.h"

void Solution::recoverTree(TreeNode* root)
{
	if (root == nullptr) {
		return;
	}
	std::vector<int> InOrderValues;
	InOrderTraversal(root, InOrderValues);
	std::pair<int, int> SwapedNodeValues = findSwapNode(InOrderValues);
	if (SwapedNodeValues.first == -1 || SwapedNodeValues.second == -1) {
		return;
	}
	doRecover(root, SwapedNodeValues.first, SwapedNodeValues.second, 2);
}

void Solution::doRecover(TreeNode* root, const int x, const int y, int counter)
{
	if (root == nullptr) {
		return;
	}
	else {
		if (root->val == x || root->val == y) {
			root->val = root->val == x ? y : x;
			if (--counter == 0) {
				return;
			}
		}
		doRecover(root->left, x, y, counter);
		doRecover(root->right, x, y, counter);
	}
}



std::pair<int, int> Solution::findSwapNode(const std::vector<int> InOrderValues)
{
	int x = -1, y = -1;
	for (int i = 0; i < InOrderValues.size() - 1; i++) {
		if (InOrderValues[i] > InOrderValues[i + 1]) {
			y = InOrderValues[i + 1];
			if (x == -1) {
				x = InOrderValues[i];
			}
			else {
				break;
			}
		}
	}
	return std::pair<int, int>(x,y);
}

void Solution::InOrderTraversal(TreeNode* root, std::vector<int>& InOrderValues)
{
	if (root == nullptr) {
		return;
	}
	else {
		InOrderTraversal(root->left, InOrderValues);
		InOrderValues.push_back(root->val);
		InOrderTraversal(root->right, InOrderValues);
	}
}
