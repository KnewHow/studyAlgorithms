# Question

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

```
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
```

Example 2:

```
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
```

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-interval
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

按照上面一题的思路，把新的区间插进去，然后重新排序,时间复杂度为`O(lgN)`

```c++
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
```

