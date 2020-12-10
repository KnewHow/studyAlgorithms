#include<iostream>
#include<vector>
#include "Solution.h"

void printVector(const std::vector<int> nums) {
	std::cout << "[ ";
	for (auto num : nums) {
		std::cout << num << ", ";
	}
	std::cout << "]" << std::endl;
}

int main() {
	std::vector<int> nums1 = { 1,0 };
	std::vector<int> nums2 = { 2 };
	int m = 1;
	int n = 1;
	Solution s;
	s.merge(nums1, m, nums2, n);
	printVector(nums1);
	std::cin.get();
	return 0;
}