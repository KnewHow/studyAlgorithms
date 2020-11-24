#include<vector>
#include<iostream>
#include "Solution.h"

void printMatrix(std::vector<std::vector<int>> matrix) {
	std::vector<int>::size_type row = matrix.size();
	std::vector<int>::size_type col = matrix[0].size();
	std::cout << "[ ";
	for (std::vector<int>::size_type i = 0; i < row; i++) {
		std::cout << "[ ";
		for (std::vector<int>::size_type j = 0; j < col; j++) {
			std::cout << matrix[i][j];
			if (j < col - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]";
		if (i< row - 1) {
			std::cout << ", ";
		}
		
	}
	std::cout << "]\n";
}


int main() {
	std::vector<std::vector<int>> matrix = { 
		{0,1,2,0},
		{3,4,5,2},
		{1,3,1,5}
	};
	Solution s;
	s.setZeroes3(matrix);
	printMatrix(matrix);
	std::cin.get();
	return 0;
}