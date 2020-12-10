#include "Solution.h"

std::vector<int> Solution::grayCode(int n)
{	
	std::vector<int> res = { 0 };
	res.reserve(2 ^ n);
	int head = 1;
	for (int i = 0; i < n; i++) {
		for (int j = res.size() - 1; j >= 0; j--) {
			res.push_back(res[j] + head);
		}
		head <<= 1;
	}
	return res;
}
