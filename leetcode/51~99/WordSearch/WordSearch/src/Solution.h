#pragma once

#include<string>
#include<vector>
#include<iostream>
class Solution {
public:
	
	// ̽�ⷢ�ĸ�����
	static const std::vector<std::pair<int, int>> DIRECTION;
	
	bool exist(std::vector<std::vector<char>>& board, std::string word);

	/**
	* �ж� row �� col �Ƿ��ǺϷ����к���
	*/
	bool isValidRowAndCol(
		const int& row,
		const int& col,
		const int& m,
		const int& n
	);

	/**
* ������ȱ���
* @param board ԭʼ���ַ�����
* @param state ״̬��ǣ�state[row][col] Ϊ true ��ʾ�õ�Ԫ���Ѿ���ʹ��
* @param row ��ǰ��
* @param col ��ǰ��
* @param word ��Ҫ���ҵĵ���
* @param k ��ǰ�жϵ� word �еĵ�k��Ԫ��
* @param m ������size
* @param n ������size
* @return ȫ��ƥ�䷵��true,���򷵻�false
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