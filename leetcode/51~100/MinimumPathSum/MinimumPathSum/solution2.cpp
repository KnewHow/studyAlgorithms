#include<vector>
#include<algorithm>
using namespace std;

class Solution2 {
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