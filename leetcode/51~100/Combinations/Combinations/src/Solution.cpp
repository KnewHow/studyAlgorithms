#include "Solution.h"

std::vector<std::vector<int>> Solution::combine(int n, int k)
{
	std::vector<int> nums;
	std::vector <std::vector<int>> res;
	for (int i = 1; i <= n; i++) {
		nums.push_back(i);
	}
	std::vector<int> tmp = {};
	tmp.reserve(k);
	doCombine(nums, res, k, -1,0,tmp);
	return res;
}

void Solution::doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // 取到k个
		res.push_back(tmp);
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

std::vector<std::vector<int>> Solution::combine2(int n, int k)
{
	std::vector<std::vector<int>> res;
	std::vector<int> temp;
	// 初始化
		// 将 temp 中 [0, k - 1] 每个位置 i 设置为 i + 1，即 [0, k - 1] 存 [1, k]
		// 末尾加一位 n + 1 作为哨兵
	for (int i = 1; i <= k; ++i) {
		temp.push_back(i);
	}
	temp.push_back(n + 1);

	int j = 0;
	while (j < k) {
		res.emplace_back(temp.begin(), temp.begin() + k);
		j = 0;
		// 寻找第一个 temp[j] + 1 != temp[j + 1] 的位置 t
		// 我们需要把 [0, t - 1] 区间内的每个位置重置成 [1, t]
		while (j < k && temp[j] + 1 == temp[j + 1]) {
			temp[j] = j + 1;
			++j;
		}
		// j 是第一个 temp[j] + 1 != temp[j + 1] 的位置
		++temp[j];
	}
	return res;
}
