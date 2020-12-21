#include<vector>
#include<algorithm>
using namespace std;
class Solution {
    struct cmp {

        bool operator() (const vector<int>& v1, const vector<int>& v2){
            if (v1.at(0) < v2.at(0)) {
                return true;
            }
            else {
                return false;
            }

        }

    };
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp());
        vector<vector<int>> merged = vector<vector<int>>();
        vector<vector<int>>::iterator begin = intervals.begin();
        vector<vector<int>>::iterator end = intervals.end();
        while (begin != end) {
            vector<int> interval = *begin;
            if (merged.empty() || interval.at(0) > merged.back().at(1)) {
                merged.push_back(interval);
            }
            else {
                merged.back().at(1) = max(merged.back().at(1), interval.at(1));
            }
            begin++;
        }
        return merged;
    }
};