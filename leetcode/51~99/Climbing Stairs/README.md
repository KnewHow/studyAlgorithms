# Climbing Stairs

You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.

Example 1:

Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/climbing-stairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

可以使用动态规划来解决，代码如下：

```c++
#include<vector>
using namespace std;

class Solution {
public:
    int climb(int n, vector<int> &dp) {
        if (n <= 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        }
        else if (n == 2) {
            return 2;
        }
        else if(dp.at(n) != -1) {
            return dp.at(n);
        }
        else {
            int oneClimb = climb(n - 1, dp); // 跳一步
            int twoClimb = climb(n - 2, dp); // 跳两步
            dp[n] = oneClimb + twoClimb;
            return dp[n];
        }
    }
    int climbStairs(int n) {
        vector<int> dp = vector<int>();
        for (int i = 0; i <= n; i++) {
            dp.push_back(-1);
        }
        return climb(n, dp);
    }
};
```

