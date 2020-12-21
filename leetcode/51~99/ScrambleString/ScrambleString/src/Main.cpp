#include <string>
#include <iostream>
#include "Solution.h"

int main() {
	Solution s;
	std::string s1 = "great";
	std::string s2 = "rgeat";
	std::string s3 = "great";
	bool r = s1 == s3;
	bool res = s.isScramble(s1, s2);
	std::cout << "res is: " << res << std::endl;
	std::cin.get();
	return 0;
}