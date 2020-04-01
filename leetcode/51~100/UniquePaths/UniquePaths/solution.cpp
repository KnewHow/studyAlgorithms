#include<vector>
using namespace std;
static int dp[101][101] = { 0 };
class Solution {
public:
	int uniquePaths(int m, int n) {
		if (m <= 0 || n <= 0) {
			return 0;
		}
		else if (m == 1 && n == 1) {
			return 1;
		}
		else if (m == 2 && n == 2) {
			return 2;
		}
		else if ((m == 3 && n == 2)||(m == 2 && n == 3)) {
			return 3;
		}
		else if (dp[m][n] > 0) {
			return dp[m][n];
		}
		else {
			dp[m][n-1] = uniquePaths(m, n - 1);
			dp[m-1][n] = uniquePaths(m - 1, n);
			dp[m][n] = dp[m - 1][n] + dp[m][n - 1];
			return dp[m][n];
		}

	}
};