#include<iostream>
#include<string>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	string numStr= "53.5e93 ";
	bool r = s.isNumber(numStr);
	cout << "is number:" << r << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}