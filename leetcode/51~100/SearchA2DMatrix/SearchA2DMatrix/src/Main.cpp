#include<vector>
#include<iostream>
#include "Solution.h"
int main() {
	std::vector<std::vector<int>> matrix = {
		{1}
	};
	int target = 0;
	Solution s;
	bool r = s.searchMatrix(matrix, target);
	std::cout << "result is:" << r << std::endl;
	std::cin.get();
	return 0;
}