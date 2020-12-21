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

std::vector<std::vector<int>> Solution::combine2(int n, int k)
{
	std::vector<std::vector<int>> res;
	std::vector<int> temp;
	// ��ʼ��
		// �� temp �� [0, k - 1] ÿ��λ�� i ����Ϊ i + 1���� [0, k - 1] �� [1, k]
		// ĩβ��һλ n + 1 ��Ϊ�ڱ�
	for (int i = 1; i <= k; ++i) {
		temp.push_back(i);
	}
	temp.push_back(n + 1);

	int j = 0;
	while (j < k) {
		res.emplace_back(temp.begin(), temp.begin() + k);
		j = 0;
		// Ѱ�ҵ�һ�� temp[j] + 1 != temp[j + 1] ��λ�� t
		// ������Ҫ�� [0, t - 1] �����ڵ�ÿ��λ�����ó� [1, t]
		while (j < k && temp[j] + 1 == temp[j + 1]) {
			temp[j] = j + 1;
			++j;
		}
		// j �ǵ�һ�� temp[j] + 1 != temp[j + 1] ��λ��
		++temp[j];
	}
	return res;
}
