#include<iostream>
#include<vector>
#include "Solution.h"

int main() {
	Solution s;
	std::vector<int> nums = { };
	int target = 3;
	bool r = s.search(nums, target);
	std::cout << "r is: " << r << std::endl;
	std::cin.get();
	return 0;
}