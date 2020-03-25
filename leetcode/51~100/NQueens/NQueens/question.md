# Question

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

![](8-queens.png)

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

```
Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：暴力法

对于棋盘中的每个格子来说，都有两种情况：

* 放入 Q
* 不放 Q

因此我们可以递归的解决这样的问题，直到将 n 个皇后都放入棋盘中，代码如下：

```java
class Solution {
   public boolean valid(List<Integer> r) {
		int n = r.size();
		int[][] chessboard = new int[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				chessboard[i][j] = 0;
			}
		}
		for (Integer nth : r) {
			int row = nth / n;
			int col = nth % n;
			chessboard[row][col] = 1;
		}
		for (Integer nth : r) {
			if (!validSingle(chessboard, nth, n)) {
				return false;
			}
		}
		return true;
	}

	public boolean validSingle(int[][] chessboard, Integer nth, int n) {

		int row = nth / n;
		int col = nth % n;
		// valid row
		for (int j = 0; j < n; j++) {
			if (j != col && chessboard[row][j] == 1) {
				return false;
			}
		}
		// valid col
		for (int i = 0; i < n; i++) {
			if (i != row && chessboard[i][col] == 1) {
				return false;
			}
		}
		// valid leading diagonal(主对角线)
		for (int i = 1; i < n; i++) {
			int beforeRow = row - i;
			int beforeCol = col - i;
			int nextRow = row + i;
			int nextCol = col + i;
			if (beforeRow >= 0 && beforeRow < n && beforeCol >= 0 && beforeCol < n) {
				if (chessboard[beforeRow][beforeCol] == 1) {
					return false;
				}
				if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n) {
					if (chessboard[nextRow][nextCol] == 1) {
						return false;
					}
				}
			}
		}

		// valid no-leading diagonal(副对角线)
		for (int i = 1; i < n; i++) {
			int beforeRow = row - i;
			int beforeCol = col + i;
			int nextRow = row + i;
			int nextCol = col - i;
			if (beforeRow >= 0 && beforeRow < n && beforeCol >= 0 && beforeCol < n) {
				if (chessboard[beforeRow][beforeCol] == 1) {
					return false;
				}
				if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n) {
					if (chessboard[nextRow][nextCol] == 1) {
						return false;
					}
				}
			}
		}

		return true;

	}

	/**
	 * 递归的解决 N queens 问题
	 * 
	 * @param nth        当前寻找到第 nth 个格子
	 * @param total      总共有多少个格子
	 * @param leftQueens 剩余未放置的皇后个数
	 * @param previous   之前存储的结果，list 中表示之前的皇后存在在第几个格子，以行位优先计算
	 * @param res        存储最终的合法的结果
	 */
	public void solve(int nth, int total, int leftQueens, List<Integer> previous, List<List<String>> res) {
		if (leftQueens == 0) { // 放完了
			if (valid(previous)) { // 如果校验通过
				res.add(genStringRes(previous));
			}
		} else {
			if (nth < total) {
				// 不放皇后
				solve(nth + 1, total, leftQueens, new ArrayList<Integer>(previous), res);
				//
				List<Integer> np = new ArrayList<Integer>(previous);
				np.add(nth);
				solve(nth + 1, total, leftQueens - 1, np, res);
			}
		}
	}

	public List<String> genStringRes(List<Integer> r) {
		List<String> res = new ArrayList<String>();
		int n = r.size();
		char[][] chessboard = new char[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				chessboard[i][j] = '.';
			}
		}
		for (Integer nth : r) {
			int row = nth / n;
			int col = nth % n;
			chessboard[row][col] = 'Q';
		}
		for (int row = 0; row < n; row++) {
			StringBuilder sb = new StringBuilder();
			for (int col = 0; col < n; col++) {
				char c = chessboard[row][col];
				sb.append(c);
			}
			res.add(sb.toString());
		}
		return res;
	}

	public List<List<String>> solveNQueens(int n) {
		List<List<String>> res = new ArrayList<List<String>>();
		solve(0, n*n, n, new ArrayList<Integer>(), res);
		return res;
	}
}
```

算法应该是正确的，但是对于`n x n`的棋盘，从第一个格子开始，每次都会产生2种情况，最后校验是否正确需要花费`O(N^2)`,因此总的时间复杂度位`O(2^(n^2) * n^2)`，当`n=8`时，需要调用`2^64 * 64` 次，在 leetcode 上超时了。

