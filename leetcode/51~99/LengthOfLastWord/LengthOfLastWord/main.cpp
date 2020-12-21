#include<iostream>
#include<string>
#include"solution.cpp"
using namespace std;

int main() {
	string s = "a ";
	Solution so = Solution();
	int r = so.lengthOfLastWord(s);
	cout << "r is:" << r << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}