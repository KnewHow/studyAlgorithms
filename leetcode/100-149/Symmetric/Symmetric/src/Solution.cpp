#include "Solution.h"
bool Solution::isSymmetric(TreeNode* root)
{
	return check(root, root);
}

bool Solution::check(TreeNode* p, TreeNode* q)
{
	if (p == nullptr && q == nullptr) {
		return true;
	}
	else if (p != nullptr && q != nullptr) {
		return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
	}
	else {
		return false;
	}
}


