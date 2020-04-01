#include<iostream>
#include<vector>
#include"solution.cpp"
using namespace std;

int main() {
	Solution s = Solution();
	vector<vector<int>> v = vector<vector<int>>();
	int m = 1;
	int n = 2;
	for (int i = 0; i < m; i++) {
		vector<int> row = vector<int>();
		for (int j = 0; j < n; j++) {
			row.push_back(0);
		}
		v.push_back(row);
	}
	v[0][1] = 1;
	int r = s.uniquePathsWithObstacles(v);
	cout << "r is: " << r << endl;
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}