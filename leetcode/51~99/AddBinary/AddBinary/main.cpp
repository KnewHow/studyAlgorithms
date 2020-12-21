#include<iostream>
#include<string>
#include"solution.cpp"
using namespace std;

int main() {
	string a = "1010";
	string b = "1011";
	Solution s = Solution();
	string r = s.addBinary(a, b);
	cout << "sum is: " << r << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}