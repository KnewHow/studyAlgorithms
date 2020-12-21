#include "Solution.h"

int Solution::maxDepth(TreeNode* root)
{
	if (root == nullptr) {
		return 0;
	}
	else {
		return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
}
