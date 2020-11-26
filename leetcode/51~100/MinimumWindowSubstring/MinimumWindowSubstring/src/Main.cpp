#include<string>
#include<iostream>
#include "Solution.h"
#include<unordered_map>

int main() {
	std::string s = "ADOBECODEBANC";
	std::string t = "ABC";
	Solution so;
	std::string r = so.minWindow(s, t);
	std::cout << "result: " << r << std::endl;
	//
	const std::unordered_map<char, int> map = {
		{'A',1},
		{'B',2}
	};
	auto i = map.find('B');
	auto e = map.end();
	std::cin.get();
}