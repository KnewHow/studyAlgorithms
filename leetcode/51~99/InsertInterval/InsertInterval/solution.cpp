#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        vector<vector<int>> merged = vector<vector<int>>();
        sort(intervals.begin(), intervals.end(), [](const vector<int>& v1, const vector<int>& v2) {
            if (v1.at(0) < v2.at(0)) {
                return true;
            }
            else {
                return false;
            }
          }
        );

        for (auto begin = intervals.begin(); begin != intervals.end(); begin++) {
            vector<int> interval = *begin;
            if (merged.empty() || interval.at(0) > merged.back().at(1)) {
                merged.push_back(interval);
            }
            else {
                merged.back().at(1) = max(merged.back().at(1), interval.at(1));
            }
        }
        return merged;
    }
};