#include "Solution.h"

int Solution::maximalRectangle(std::vector<std::vector<char>>& matrix)
{
	if (matrix.size() == 0) {
		return 0;
	}
	else {
		int res = 0;
		int m = matrix.size();
		int n = matrix[0].size();
		std::vector<int> heights(n, 0);
		for (int row = 0; row < matrix.size(); row++) {
			for (int col = 0; col < n; col++) {
				if (matrix[row][col] == '1') {
					heights[col]++;
				}
				else {
					heights[col] = 0;
				}
			}
			int temp = getMaxRectangleInHistogram(heights);
			res = std::max(res, temp);
		}
		return res;
	}
}

int Solution::getMaxRectangleInHistogram(const std::vector<int>& heights)
{
	int n = heights.size();
	std::stack<int> stack;
	std::vector<int> left(n), right(n, n);
	for (int i = 0; i < n; i++) {
		while (!stack.empty() && heights[stack.top()] >= heights[i]) {
			right[stack.top()] = i;
			stack.pop();
		}
		left[i] = stack.empty() ? -1 : stack.top();
		stack.push(i);
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		res = std::max(res, (right[i] - left[i] - 1) * heights[i]);
	}
	return res;
}
