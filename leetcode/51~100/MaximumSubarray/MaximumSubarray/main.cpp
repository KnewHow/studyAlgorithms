#include<iostream>
#include"solution.cpp"

using namespace std;

int main() {
	vector<int> v = { -2,1};
	Solution s = Solution();
	int r = s.maxSubArray_2(v);
	cout << "r is " << r << endl;
	cin.get();
	return 0;
}