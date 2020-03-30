#include<iostream>
#include<vector>
#include"solution.cpp"
using namespace std;


int main() {
	vector<vector<int>> intervals = vector<vector<int>>();
	intervals.push_back({ 1,2 });
	intervals.push_back({ 3,5 });
	intervals.push_back({ 6,7 });
	intervals.push_back({ 8,10 });
	intervals.push_back({ 12,16 });
	vector<int> newInterval = { 4,8 };
	Solution s = Solution();
	vector<vector<int>> r = s.insert(intervals, newInterval);
	cout << "[ ";
	for (auto begin = r.begin(); begin != r.end(); begin++) {
		vector<int> interval = *begin;
		cout << "[ ";
		for (auto b = interval.begin(); b != interval.end(); b++) {
			cout << *b << " ";
		}
		cout << "]";
	}
	cout << " ]" << endl;
	cout << "please press any key to go on...";
	cin.get();
	return 0;
}