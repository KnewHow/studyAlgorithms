#include<iostream>
#include<string>
#include "Solution.h"

int main() {
	Solution solution;
	std::string s = "111111111111111111111111111111111111111111111";
	int res = solution.numDecodings(s);
	std::cout << "res is: " << res << std::endl;
	std::cin.get();
	return 0;
}