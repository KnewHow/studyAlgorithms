#include<iostream>
#include<string>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	int n = 4;
	int k = 9;
	string r = s.getPermutation(n, k);
	cout << "r is:" << r << endl;
	cout << "please press any key to go on" << endl;
	cin.get();
	return 0;
}