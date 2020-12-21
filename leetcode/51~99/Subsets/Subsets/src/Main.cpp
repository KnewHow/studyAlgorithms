#include<vector>
#include<iostream>
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
	std::vector<int> nums = { 1,2,2 };
	Solution s;
	auto res = s.subsets(nums);
	printRes(res);
	std::cin.get();
}