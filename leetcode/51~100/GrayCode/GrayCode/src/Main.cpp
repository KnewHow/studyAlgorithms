#include<iostream>
#include<vector>
#include "Solution.h"
void printNums(std::vector<int> nums) {
	std::cout << "[";
	for (auto num : nums) {
		std::cout << num << ", ";
	}
	std::cout << "]" << std::endl;
}

int main() {
	Solution s;
	int n = 2;
	std::vector<int> res = s.grayCode(n);
	printNums(res);
	std::cin.get();
	return 0;
}