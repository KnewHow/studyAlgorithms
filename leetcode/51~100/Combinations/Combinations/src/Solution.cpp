#include "Solution.h"

std::vector<std::vector<int>> Solution::combine(int n, int k)
{
	std::vector<int> nums;
	std::vector <std::vector<int>> res;
	for (int i = 1; i <= n; i++) {
		nums.push_back(i);
	}
	doCombine(nums, res, k, 0);
	return res;
}

void Solution::doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int nth)
{
	if (nth == k) { // k 个元素全部找完
		std::vector<int> r(nums.begin(), nums.begin() + k);
		res.push_back(r);
	}
	else {
		for (int i = nth; i < nums.size(); i++) {
			swap(nums, nth, i);
			doCombine(nums, res, k, nth + 1);
			swap(nums, nth, i);
		}
	}
}

void Solution::swap(std::vector<int>& v, int i, int j)
{
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
