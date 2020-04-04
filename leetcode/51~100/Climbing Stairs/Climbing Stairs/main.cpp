#include<iostream>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	int n = 3;
	int sum = s.climbStairs(n);
	cout << "sum is:" << sum << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}