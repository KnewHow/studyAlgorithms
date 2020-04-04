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