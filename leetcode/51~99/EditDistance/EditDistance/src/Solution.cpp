#include "Solution.h"

int Solution::minDistance(std::string word1, std::string word2)
{
	const std::string::size_type size1 = word1.size();
	const std::string::size_type size2 = word2.size();
	std::vector<std::vector<int>> dp(size1 + 1, std::vector<int>(size2 + 1, 0));
	for (int i = 0; i <= size1; i++) {
		dp[i][0] = i;
	}
	for (int j = 0; j <= size2; j++) {
		dp[0][j] = j;
	}

	for (int i = 1; i <= size1; i++) {
		for (int j = 1; j <= size2; j++) {
			int down = dp[i - 1][j] + 1;
			int left = dp[i][j - 1] + 1;
			int leftDown = dp[i - 1][j - 1] + 1;
			if (word1[i - 1] == word2[j - 1]) {
				leftDown = leftDown - 1;
			}
			dp[i][j] = std::min(leftDown, std::min(down, left));
		}
	}

	return dp[size1][size2];
}
