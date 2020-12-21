#include "Solution.h"

const std::vector<std::pair<int, int>> Solution::DIRECTION = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};

bool Solution::exist(std::vector<std::vector<char>>& board, std::string word)
{
	int m = board.size();
	int n = board[0].size();
	std::vector<std::vector<bool>> state;
	for (int i = 0; i < m; i++) {
		std::vector<bool> v;
		for (int j = 0; j < n; j++) {
			v.push_back(false);
		}
		state.push_back(v);
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (dfs(board, state, i, j, word, 0, m, n)) {
				return true;
			}
		}
	}
	return false;
}




bool Solution::isValidRowAndCol(
	const int& row, 
	const int& col, 
	const int& m, 
	const int& n
)
{
	if (row >= 0 && row < m && col >= 0 && col < n) {
		return true;
	}
	else {
		return false;
	}
}

bool Solution::dfs(
	std::vector<std::vector<char>>& board, 
	std::vector<std::vector<bool>>& state, 
	int row, 
	int col, 
	const std::string& word, 
	int k,
	const int& m,
	const int& n
)
{
	if (k == word.size() - 1) {
		return board[row][col] == word[k];
	}

	if (board[row][col] == word[k]) {
		state[row][col] = true;
		for (int i = 0; i < 4; i++) {
			std::pair<int, int> d = DIRECTION[i];
			int nextRow = row + d.first;
			int nextCol = col + d.second;
			if (isValidRowAndCol(nextRow, nextCol, m, n) &&
				!state[nextRow][nextCol]) {
				// 
				if (dfs(board, state, nextRow, nextCol, word, k + 1, m, n)) {
					return true;
				 }
			}
		}
	}
	// 如果从循环中出来，不论结果如何，该单元格匹配失败
	state[row][col] = false;
	return false;
}