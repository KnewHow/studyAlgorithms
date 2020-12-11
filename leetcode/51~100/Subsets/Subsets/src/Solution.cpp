#include "Solution.h"

std::vector<std::vector<int>> Solution::subsets(std::vector<int>& nums)
{
	std::vector <std::vector<int>> res;
	std::vector<int> tmp = {};
	res.push_back({});
	for (int i = 1; i <= nums.size(); i++) {
		doCombine(nums, res, i, -1, 0, tmp);
	}
	return res;
}

void Solution::doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // ȡ��k��
		res.push_back(tmp);
		return;
	}

	// ���ʣ�µ�Ԫ�ز����Թ�����ϣ�ֱ����ȥ
	if (k - kth > nums.size() - previousIndex - 1) {
		return;
	}

	for (int i = previousIndex + 1; i < nums.size(); i++) {
		tmp.push_back(nums[i]);
		doCombine(nums, res, k, i, kth + 1, tmp);
		tmp.pop_back();
	}
}