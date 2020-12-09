#include<iostream>
#include<vector>
#include "Solution.h"

int main() {
	Solution s;
	std::vector<std::vector<char>> matrix = {
		{'1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '0'},
		{'1', '1', '1', '1', '1', '1', '1', '0'},
		{'1', '1', '1', '1', '1', '0', '0', '0'},
		{'0', '1', '1', '1', '1', '0', '0', '0'}
	};
	int res = s.maximalRectangle(matrix);
	std::cout << "res is: " << res << std::endl;
	std::cin.get();
	return 0;
}