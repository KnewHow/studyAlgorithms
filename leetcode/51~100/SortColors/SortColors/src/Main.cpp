#include<iostream>
#include<vector>
#include "Solution.h"

void printNums(const std::vector<int> nums) {
	std::cout << "[ ";
	for (int num : nums) {
		std::cout << num << " ";
	}
	std::cout << "] " << std::endl;
}

int main() {
	std::vector<int> nums = { 2,0,2,1,1,0 };
	Solution s;
	s.sortColors4(nums);
	printNums(nums);
	std::cin.get();
	return 0;
}