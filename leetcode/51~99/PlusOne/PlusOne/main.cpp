#include<iostream>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	vector<int> v = { 1,2,3 };
	s.plusOne(v);
	s.printDigits(v);
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}