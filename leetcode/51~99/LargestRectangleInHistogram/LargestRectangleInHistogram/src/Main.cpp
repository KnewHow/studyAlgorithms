#include<iostream>
#include<vector>
#include "Solution.h"

int main() {
	std::vector<int> v1(3);
	std::vector<int> v2(3,1);
	std::vector<int> v3 = { 0 };
	std::vector<int> heights = { 2,1,5,6,2,3 };
	Solution s;
	int res = s.largestRectangleArea_Height(heights);
	std::cout << "res is: " << res << std::endl;
	std::cin.get();
	return 0;
}