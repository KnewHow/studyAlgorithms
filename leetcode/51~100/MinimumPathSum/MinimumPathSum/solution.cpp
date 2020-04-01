#include<vector>
#include<algorithm>
using namespace std;
#define MAX_ROW 201
class Solution {
public:
    int solve(vector<vector<int>>& grid, int m, int n, int originalM, int originalN, int dp[MAX_ROW][MAX_ROW]) {
        if (m == 0 || n == 0) {
            return INT_MAX;
        }
        else if (m == 1 && n == 1) {
            return grid[originalM - m][originalN - n];
        }
        else if(dp[m][n] != -1) {
            return dp[m][n];
        }
        else {
            dp[m - 1][n] = solve(grid, m - 1, n, originalM, originalN, dp);
            dp[m][n - 1] = solve(grid, m, n - 1, originalM, originalN, dp);
            dp[m][n] = grid[originalM - m][originalN - n] + min(dp[m - 1][n], dp[m][n - 1]);
            if (m == originalM && n == originalN) {
                int a = 3;
            }
            return dp[m][n];
        }
    }
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) {
            return 0;
        }
        else {
            int n = grid.at(0).size();
            int dp[MAX_ROW][MAX_ROW] = { 0 };
            for (int i = 0; i < MAX_ROW; i++) {
                for (int j = 0; j < MAX_ROW; j++) {
                    dp[i][j] = -1;
                }
            }
            return solve(grid, m, n, m, n, dp);
        }
    }
};