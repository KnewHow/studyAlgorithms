# Question

Given a collection of intervals, merge all overlapping intervals.

Example 1:

```
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
```


Example 2:

```
Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
```

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-intervals
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

参考[官方题解的解法二](https://leetcode-cn.com/problems/merge-intervals/solution/he-bing-qu-jian-by-leetcode/)，使用排序的方式来解

```c++
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
```

