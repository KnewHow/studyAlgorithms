#include<iostream>
#include<vector>
#include "Weapon.h";
#include "Solution.h"

void printRes(const std::vector<std::vector<int>>& res) {
	std::cout << "[" << std::endl;
	for (const auto v : res) {
		std::cout << "[ ";
		for (const int e : v) {
			std::cout << e;
			std::cout << " ";
		}
		std::cout << "]" << std::endl;
	}
	std::cout << "]";
}

int main() {
	int n = 4;
	int k = 2;
	Solution s;
	auto res = s.combine(n, k);
	printRes(res);
	std::cin.get();
	return 0;
}