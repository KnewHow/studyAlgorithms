#include<iostream>
#include<vector>
#include"solution.cpp"
using namespace std;

int main() {
	vector<int> nums = { 1,1,0,1 };
	Solution s = Solution();
	bool r = s.canJump(nums);
	cout << "r is:" << r << endl;
	cout << "press any key go on..." << endl;
	cin.get();
	return 0;
}