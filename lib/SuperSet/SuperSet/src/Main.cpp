#include<iostream>
#include<vector>
#include<unordered_set>
#include "MySet.h"

int main() {
	MySet set;
	std::vector<int> v = { 1,2,3 };
	set.insert(v);
	std::cin.get();
	return 0;
}