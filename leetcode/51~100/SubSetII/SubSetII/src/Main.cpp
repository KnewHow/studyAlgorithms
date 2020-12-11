#include<iostream>
#include<vector>
#include "Solution.h"

void printRes(const std::vector<std::vector<int>>& res) {
	std::cout << "[" << std::endl;
	for (const auto v : res) {
		std::cout << "[ ";
		for (const int e : v) {
			std::cout << e;
			std::cout << " ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]";
}

int main() {
	std::vector<int> nums = { 4,4,4,1,4 };
	Solution s;
	auto res = s.subsetsWithDup(nums);
	printRes(res);
	std::cin.get();
	return 0;
}