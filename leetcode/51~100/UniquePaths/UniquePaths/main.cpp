#include<iostream>
#include"solution.cpp"
using namespace std;

int main() {
	int m = 19;
	int n = 13;
	Solution s = Solution();
	int total = s.uniquePaths(m, n);
	cout << "total is:" << total << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}