#include<iostream>
#include<vector>
#include"solution.cpp"
#include"solution2.cpp"
using namespace std;

int main() {
	Solution2 s = Solution2();
	vector<vector<int>> v = vector<vector<int>>();
	vector<int> r1 = { 1,3,1 };
	vector<int> r2 = { 1,5,1 };
	vector<int> r3 = { 4,2,1 };
	v.push_back(r1);
	v.push_back(r2);
	v.push_back(r3);
	int r = s.minPathSum(v);
	cout << "r is:" << r << endl;
	cout << "please pres any key to go on..." << endl;
	cin.get();
	return 0;
}