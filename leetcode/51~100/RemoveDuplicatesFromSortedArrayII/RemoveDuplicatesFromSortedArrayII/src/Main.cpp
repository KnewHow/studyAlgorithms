#include<iostream>
#include<vector>
#include "Solution.h"

void printNums(std::vector<int> nums, int len) {
	for (int i = 0; i < len; i++) {
		std::cout << nums[i] << std::endl;
	}
}

int main() {
	Solution s;
	std::vector<int> nums = { 1,1,1,2 };
	int len = s.removeDuplicates(nums);
	std::cout << "Len is: " << len << std::endl;
	printNums(nums, len);
	std::cin.get();
	return 0;
}