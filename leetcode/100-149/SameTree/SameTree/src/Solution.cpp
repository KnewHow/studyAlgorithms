#include "Solution.h"

bool Solution::isSameTree(TreeNode* p, TreeNode* q)
{
	if (p == nullptr && q == nullptr) {
		return true;
	}
	else if(p != nullptr &&  q != nullptr) {
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
	else {
		return false;
	}
}
