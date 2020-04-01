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