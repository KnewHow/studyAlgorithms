#include "Solution.h"

std::vector<std::vector<int>> Solution::subsetsWithDup(std::vector<int>& nums)
{
	std::vector<std::vector<int>> res;
	res.push_back({});
	std::vector<int> temp;
	std::sort(nums.begin(), nums.end()); // 排序，防止元素错序导致跳过失败
	for (int i = 1; i <= nums.size(); i++) {
		doCombine_DeleteRepeat(nums, res, i, -1, 0, temp);
	}
	return res;
}

void Solution::doCombine_DeleteRepeat(const std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // 取到k个
		res.push_back(tmp);
		return;
	}

	// 如果剩下的元素不足以构成组合，直接舍去
	if (k - kth > nums.size() - previousIndex - 1) {
		return;
	}
	int previousElement = 0;
	for (int i = previousIndex + 1; i < nums.size(); i++) {
		if (i == previousIndex + 1) {
			previousElement = nums[i];
			tmp.push_back(nums[i]);
			doCombine_DeleteRepeat(nums, res, k, i, kth + 1, tmp);
			tmp.pop_back();
		}
		else {
			if (previousElement == nums[i]) {// same position can't put same element twice, do nothing here
				continue;
			}
			else {
				previousElement = nums[i];
				tmp.push_back(nums[i]);
				doCombine_DeleteRepeat(nums, res, k, i, kth + 1, tmp);
				tmp.pop_back();
			}
		}
		
	}
}

std::vector<std::vector<int>> Solution::subsetsWithDup_WithOuter(std::vector<int>& nums)
{
	MySet res;
	std::vector<int> temp = {};
	for (int i = 1; i <= nums.size(); i++) {
		doCombine(nums, res, i, -1, 0, temp);
	}
	std::vector<std::vector<int>> r = std::vector<std::vector<int>>(res.begin(), res.end());
	r.push_back({});
	return r;
}

void Solution::doCombine(std::vector<int>& nums, MySet& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // 取到k个
		std::vector<int> v = tmp;
		std::sort(v.begin(), v.end()); // 复制并排序，让相同组合不同顺序的结果Hash值相同
		res.insert(v);
		return;
	}

	// 如果剩下的元素不足以构成组合，直接舍去
	if (k - kth > nums.size() - previousIndex - 1) {
		return;
	}

	for (int i = previousIndex + 1; i < nums.size(); i++) {
		tmp.push_back(nums[i]);
		doCombine(nums, res, k, i, kth + 1, tmp);
		tmp.pop_back();
	}
}
