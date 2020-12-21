#include<string>
#include<iostream>
#include "Solution.h"

int main() {
	std::string word1 = "intention";
	std::string word2 = "execution";
	Solution s;
	int r = s.minDistance(word1, word2);
	std::cout << "minum distance:" << r << std::endl;
	std::cin.get();
	return 0;
}