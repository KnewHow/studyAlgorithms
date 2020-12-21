#include<iostream>
#include<string>
#include "Solution.h"
int main() {
	Solution s;
	std::string path = "/...";
	std::string result = s.simplifyPath(path);
	std::cout << result << std::endl;
	std::cin.get();
	return 0;
}