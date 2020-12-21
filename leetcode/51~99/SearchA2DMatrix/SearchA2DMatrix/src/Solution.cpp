#include "Solution.h"

bool Solution::searchMatrix(std::vector<std::vector<int>>& matrix, int target)
{
	if (matrix.size() == 0 || matrix[0].size() == 0) {
		return false;
	}
	else {
		int row = matrix.size();
		int col = matrix[0].size();
		int begin = 0;
		int end = row * col - 1;
		while (begin <= end) {
			int  mid = (begin + end) / 2;
			int r = mid / col;
			int c = mid - r * col;
			if (matrix[r][c] == target) {
				return true;
			}
			else if (matrix[r][c] < target) {
				begin = mid + 1;
			}
			else {
				end = mid - 1;
			}
		}
		return false;
	}
	
}
