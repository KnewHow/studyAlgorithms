#include "Solution.h"

std::vector<TreeNode*> Solution::generateTrees(int n)
{
	if (n == 0) {
		return std::vector<TreeNode*>();
	}
	else {
		return doGenerate(1, n);
	}
}

std::vector<TreeNode*> Solution::doGenerate(int start, int end)
{
	if (start > end) {
		return {nullptr};
	}
	
	std::vector<TreeNode*> res;
	for (int i = start;  i <= end; i++) {
		auto lefts = doGenerate(start, i - 1);
		auto rights = doGenerate(i + 1, end);
		for (auto left : lefts) {
			for (auto right : rights) {
				TreeNode* root = new TreeNode(i, left, right);
				res.push_back(root);
			}
		}
	}
	return res;
}
