#pragma once

#include<string>
#include<vector>
#include<iostream>
class Solution {
public:
	
	// 探测发四个方向
	static const std::vector<std::pair<int, int>> DIRECTION;
	
	bool exist(std::vector<std::vector<char>>& board, std::string word);

	/**
	* 判断 row 和 col 是否是合法的行和列
	*/
	bool isValidRowAndCol(
		const int& row,
		const int& col,
		const int& m,
		const int& n
	);

	/**
* 深度优先遍历
* @param board 原始的字符矩阵
* @param state 状态标记，state[row][col] 为 true 表示该单元格已经被使用
* @param row 当前行
* @param col 当前列
* @param word 需要查找的单词
* @param k 当前判断到 word 中的第k个元素
* @param m 矩阵行size
* @param n 矩阵列size
* @return 全部匹配返回true,否则返回false
*/
	bool dfs(
		std::vector<std::vector<char>>& board,
		std::vector<std::vector<bool>>& state,
		int row,
		int col,
		const std::string& word,
		int k,
		const int& m,
		const int& n
	);
};