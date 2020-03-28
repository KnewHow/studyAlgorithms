#include<iostream>
#include<vector>
#include"solution.cpp"
using namespace std;

int main() {
	int row = 3;
	int col = 4;
	int counter = 1;
	vector<vector<int>> v = vector<vector<int>>();
	for (int i = 0; i < row; i++) {
		vector<int> t = vector<int>();
		for (int j = 0; j < col; j++) {
			int v = counter;
			counter++;
			t.push_back(v);
		}
		v.push_back(t);
	}
	Solution s = Solution();
	vector<int> r = s.spiralOrder(v);
	cout << "[ ";
	for (int i = 0; i < r.size(); i++) {
		cout << r[i] << " ";
	}
	cout << "]" << endl;
	cout << "press any key go on" << endl;
	cin.get();
	return 0;
}