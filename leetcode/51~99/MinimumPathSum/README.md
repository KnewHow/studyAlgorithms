# 64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example:

Input:
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7
Explanation: Because the path 1→3→1→1→1 minimizes the sum.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-path-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：按照之前走方格的套路

按照[62题](https://github.com/KnewHow/studyAlgorithms/tree/master/leetcode/51~100/UniquePaths)的思路，使用是个数组dp,记录每个位置的到终点的最小值即可。代码如下：

```c++
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
```

## 解法二：从右下角往左上角进行统计

参考了[官方题解的二维动态规划](https://leetcode-cn.com/problems/minimum-path-sum/solution/zui-xiao-lu-jing-he-by-leetcode/)，我们可以从矩阵右下角开始往左上角进行加法运算。

```c++
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> initMatrix(int m, int n) {
		vector<vector<int>> v = vector<vector<int>>();
		for (int i = 0; i < m; i++) {
			vector<int> row = vector<int>();
			for (int j = 0; j < n; j++) {
				row.push_back(-1);
			}
			v.push_back(row);
		}
		return v;
	}
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		if (m == 0) {
			return 0;
		}
		else {
			int n = grid.at(0).size();
			vector<vector<int>> matrix = initMatrix(m, n);
			for (int i = m - 1; i >= 0; i--) {
				for (int j = n - 1; j >= 0; j--) {
					if (j == n - 1 && i != m - 1) { // 最后一列，只能向下累加
						matrix[i][j] = grid[i][j] + matrix[i + 1][j];
					}
					else if (i == m - 1 && j != n - 1) { // 最后一行，只能向右累计
						matrix[i][j] = grid[i][j] + matrix[i][j + 1];
					}
					else if(i != m-1 && j != n-1) { // 不是最后一行和最后一列
						matrix[i][j] = grid[i][j] + min(matrix[i + 1][j], matrix[i][j + 1]);
					}
					else { // 终点
						matrix[i][j] = grid[i][j];
					}
				}
			}
			return matrix[0][0];
		}
	}
};
```



