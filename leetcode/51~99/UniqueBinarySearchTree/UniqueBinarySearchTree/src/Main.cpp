#include<iostream>
#include "Solution.h"

int& add(int a, int b) {
	int i;
	i = 1;
	return i;
}

int main() {
	Solution s;
	int r = add(3, 4);
	int n = 19;
	int res = s.numTrees2(n);
	std::cout << "r is: " << r << std::endl;
	std::cout << "res is: " << res << std::endl;
	std::cin.get();
	return 0;
}