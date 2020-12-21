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
	std::vector<int> v1 = { 1,2,3 };
	std::vector<int> v2 = { 1,2,3 };
	bool r = v1 == v2;
	Solution s;
	int n = 2;
	std::vector<int> res = s.grayCode(n);
	printNums(res);
	std::cin.get();
	return 0;
}