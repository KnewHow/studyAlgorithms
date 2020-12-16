#include "Solution.h"

bool Solution::isInterleave(std::string s1, std::string s2, std::string s3)
{
	int m = s1.size(), n = s2.size(), t = s3.size();
	std::vector<std::vector<int>> res = std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, 0));
	if (m + n != t) {
		return false;
	}
	res[0][0] = 1;
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			int p = i + j - 1;
			if (i > 0) {
				res[i][j] |= (res[i - 1][j] && s1[i - 1] == s3[p]);
			}
			if (j > 0) {
				res[i][j] |= (res[i][j - 1] && s2[j - 1] == s3[p]);
			}
		}
	}
	return res[m][n];
}
