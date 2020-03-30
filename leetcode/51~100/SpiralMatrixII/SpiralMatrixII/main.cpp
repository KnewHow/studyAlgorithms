#include<iostream>
#include<vector>
#include"solution.cpp"
using namespace std;

int main() {
	int n = 3;
	Solution s = Solution();
	vector<vector<int>> r = s.generateMatrix(n);
	for (auto begin = r.begin(); begin != r.end(); begin++) {
		vector<int> row = *begin;
		for (auto b = row.begin(); b != row.end(); b++) {
			cout << *b << " ";
		}
		cout << endl;
	}
	cout << "please press any key to go on..." << endl;
	cin.get();
	return 0;
}