#include<iostream>
#include<string>
#include<vector>
#include "Solution.h"

void printRes(std::vector<std::string> res) {
	for (const auto& s : res) {
		std::cout << s << std::endl;
	}
}

int main() {
	Solution solution;
	std::string s = "0000";
	std::vector<std::string> res = solution.restoreIpAddresses(s);
	printRes(res);
	std::cin.get();
	return 0;
}