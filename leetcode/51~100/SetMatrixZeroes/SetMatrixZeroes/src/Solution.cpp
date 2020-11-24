#include "Solution.h"

void Solution::setZeroes(std::vector<std::vector<int>>& matrix)
{
	std::vector<std::vector<int>>::size_type row = matrix.size();
	std::vector<int>::size_type col = matrix[0].size();
	
	std::vector<std::vector<int>> copyed(row, std::vector<int>(col, 0));
	for (std::vector<std::vector<int>>::size_type i = 0; i < row; i++) {
		for (std::vector<int>::size_type j = 0; j < col; j++) {
			copyed[i][j] = matrix[i][j];
		}
	}

	for (std::vector<std::vector<int>>::size_type i = 0; i < row; i++) {
		for (std::vector<int>::size_type j = 0; j < col; j++) {
			if (copyed[i][j] == 0) {
				for (std::vector<std::vector<int>>::size_type m = 0; m < row; m++) {
					matrix[m][j] = 0;
				}
				for (std::vector<int>::size_type n = 0; n < col; n++) {
					matrix[i][n] = 0;
				}
			}
		}
	}
}

void Solution::setZeroes2(std::vector<std::vector<int>>& matrix)
{
	auto row = matrix.size();
	auto col = matrix[0].size();
	
	// 需要清零的行和列
	std::set<std::vector<std::vector<int>>::size_type> rowSet;
	std::set<std::vector<int>::size_type> colSet;

	for (auto i = 0; i < row; i++) {
		for (auto j = 0; j < col; j++) {
			if (matrix[i][j] == 0) {
				rowSet.insert(i);
				colSet.insert(j);
			}
		}
	}
	// 执行清零
	for (auto r : rowSet) {
		for (auto j = 0; j < col; j++) {
			matrix[r][j] = 0;
		}
	}
	for (auto c : colSet) {
		for (auto i = 0; i < row; i++) {
			matrix[i][c] = 0;
		}
	}
}

void Solution::setZeroes3(std::vector<std::vector<int>>& matrix)
{
	auto row = matrix.size();
	auto col = matrix[0].size();
	// 由于第一行和第一列作为标记位，这里来标记第一列是否全为0
	bool isCol = false;
	for (auto i = 0; i < row; i++) {
		if (matrix[i][0] == 0) {
			isCol = true;
		}
		for (auto j = 1; j < col; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}

	for (auto i = 1; i < row; i++) {
		for (auto j = 1; j < col; j++) {
			if (matrix[i][0] == 0 || matrix[0][j] == 0) {
				matrix[i][j] = 0;
			}
		}
	}
	// 标记第一行
	if (matrix[0][0] == 0) {
		for (auto j = 0; j < col; j++) {
			matrix[0][j] = 0;
		}
	}
	// 标记第一列
	if (isCol) {
		for (auto i = 0; i < row; i++) {
			matrix[i][0] = 0;
		}
	}
}
