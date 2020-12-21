#include "Solution.h"

int Solution::numTrees(int n)
{
	if (n == 0) {
		return 0;
	}
	else {
		return doParse(1, n);
	}
}

int Solution::numTrees2(int n)
{
	long long  res = 1;
	for (int i = 0; i < n; i++) {
		res = res * 2 * (2 * i + 1) / (i + 2);
	}
	return (int)res;
}

int Solution::doParse(int start, int end)
{
	if (start > end) {
		return 1;
	}
	int res = 0;
	for (int i = start; i <= end; i++) {
		int lefts = doParse(start, i - 1);
		int rights = doParse(i + 1, end);
		res += (lefts * rights);
		
	}
	return res;
}
