#include<iostream>
#include"solution.cpp"
using namespace std;

int main() {
	vector<vector<int>> intervals = vector<vector<int>>();
	vector<int> v1 = { 1,3 };
	vector<int> v2 = { 2, 6 };
	vector<int> v3 = { 8, 10 };
	vector<int> v4 = { 15,18 };
	intervals.push_back({1,4});
	intervals.push_back({ 4,5 });
	//intervals.push_back({ 8, 10 });
	//intervals.push_back({ 15,18 });
	Solution s = Solution();
	vector<vector<int>> r = s.merge(intervals);
	cout << "[";
	for (auto begin = r.begin(); begin != r.end(); begin++) {
		cout << "[";
		vector<int> interval = *begin;
		for (auto b = interval.begin(); b != interval.end(); b++) {
			cout << *b << ", ";
		}
		cout << "] ";
	}
	cout << "]" << endl;
	cout << "please press any key go on..." << endl;
	cin.get();
	return 0;
}