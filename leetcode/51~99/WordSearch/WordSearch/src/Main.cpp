#include<vector>
#include<string>
#include<iostream>
#include "Solution.h"

int main() {
	Solution s;
	std::vector<std::vector<char>>	board = {
		{'b', 'a', 'a', 'b', 'a', 'b'},
		{'a', 'b', 'a', 'a', 'a', 'a'},
		{'a', 'b', 'a', 'a', 'a', 'b'},
		{'a', 'b', 'a', 'b', 'b', 'a'},
		{'a', 'a', 'b', 'b', 'a', 'b'},
		{'a', 'a', 'b', 'b', 'b', 'a'},
		{'a', 'a', 'b', 'a', 'a', 'b'}
	};
	std::string word = "aabbbbabbaababaaaabababbaaba";
	bool res = s.exist(board, word);
	std::cout << "res is:" << res << std::endl;
	std::cin.get();
}