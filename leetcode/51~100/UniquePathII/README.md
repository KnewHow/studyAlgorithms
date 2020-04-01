# 63. Unique Paths II

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

![](..\UniquePaths\robot_maze.png)

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:

```
Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:

1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

按照之前[62题](https://github.com/KnewHow/studyAlgorithms/tree/master/leetcode/51~100/UniquePaths)的思想,让我们遇见障碍物时，直接返回0，即可。

```c++
#include<vector>
using namespace std;
class Solution {
public:
    /**
    * 
    */
    int solve(vector<vector<int>>& obstacleGrid, int m, int n, int originalM, int originalN, int dp[101][101]) {
        if (m <= 0 || n <= 0) {
            return 0;
        }
        else if (m ==1 && n==1) { 
            if (obstacleGrid[originalM-m][originalN-n] == 1) {// 此路不通
                return 0;
            }
            else {
                return 1;
            }
        }
        else if (dp[m][n] != -1) {
            return dp[m][n];
        }
        else {
            if (obstacleGrid[originalM-m][originalN-n] == 1) {// 此路不通
                dp[m][n] = 0;
                return dp[m][n];
            }
            else {
                dp[m - 1][n] = solve(obstacleGrid, m - 1, n,originalM,originalN, dp);
                dp[m][n - 1] = solve(obstacleGrid, m, n - 1, originalM, originalN, dp);
                dp[m][n] = dp[m - 1][n] + dp[m][n - 1];
                return dp[m][n];
            }
        }
    }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int dp[101][101] = { 0 };
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 101; j++) {
                dp[i][j] = -1;
            }
        }
        int m = obstacleGrid.size();
        if (m == 0) {
            return 0;
        }
        else {
            int n = obstacleGrid.at(0).size();
            return solve(obstacleGrid, m, n,m,n, dp);
        }
    }
};
```

