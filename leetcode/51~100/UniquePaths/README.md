# 62. Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

![](robot_maze.png)


Above is a 7 x 3 grid. How many possible unique paths are there?

Example 1:

```
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:

1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right
```

Example 2:

```
Input: m = 7, n = 3
Output: 28
```



Constraints:

1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 10 ^ 9.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

我们可以使用回溯法来解，定义一个`m x n` 的矩阵，然后建立一个辅助栈，每次走一步，把上次的位置信息和方向信息压入栈中，如果走到终点，进行回溯。我们以向右行走为优先，如果回溯到一个点，如果发现它上次是向右走的，可以再次尝试往下走(当然不是所有的点都是可以往两个方向走，对于某些只可以往一个方向走的格子，直接回溯)；如果发现他上次是往下走的，该点无法在回溯，继续回溯上一个点，直到回溯到(0,0)也无法回溯了。

代码如下：

```c++
#include<stack>
#include<vector>
#include<iostream>
using namespace std;
#define RIGHT 0
#define BELOW 1

// 方格
struct Grid {
    int row; // 行
    int col; // 列
    int way; // 方向 0-右侧 1-下方
    Grid(int row, int col, int way) :row(row), col(col), way(way) {};
};
class Solution {
public:
    void printMarix(vector<vector<int>> matrix) {
        cout << "print matrix begin..." << endl;
        for (auto begin = matrix.begin(); begin != matrix.end(); begin++) {
            vector<int> row = *begin;
            for (auto b = row.begin(); b != row.end(); b++) {
                cout << *b << " ";
            }
            cout << endl;
        }
        cout << "print matrix end..." << endl;
    }
    vector<vector<int>> initMatrix(int m, int n) {
        vector<vector<int>> matrix = vector<vector<int>>();
        for (int i = 0; i < m; i++) {
            vector<int> row = vector<int>();
            for (int j = 0; j < n; j++) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
        return matrix;
    }
    // 获取可以走到方向
    vector<int> getWay(int row, int col, int m, int n) {
        if (col == n - 1) {
            return  vector<int>{ BELOW };
        }
        if (row == m - 1) {
            return vector<int>{ RIGHT };
        }
        return  vector<int>{ RIGHT,BELOW };
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> matrix = initMatrix(m, n);
        int total = 0;
        stack<Grid> path = stack<Grid>();
        Grid g0 = Grid(0, 0, 0);
        path.push(g0);
        int goOrBack = 1; // 0-bakc 回溯 1-go
        int nextRow = 0;
        int nextCol = 1;
        matrix[0][0] = 1;
        while (!path.empty()) {
            if (nextRow < m && nextCol < n) {
                if (goOrBack == 1) {
                    vector<int> ways = getWay(nextRow, nextCol, m, n);
                    if (ways.size() == 2) { // 有两个方向可以走， 优先选择右方
                        Grid g = Grid(nextRow, nextCol, 0);
                        path.push(g);
                        matrix[nextRow][nextCol] = 1;
                        nextRow = nextRow;
                        nextCol = nextCol + 1;
                    }
                    else {// 只有一个方向可以走
                        int way = ways.front();
                        Grid g = Grid(nextRow, nextCol, way);
                        path.push(g);
                        matrix[nextRow][nextCol] = 1;
                        if (way == RIGHT) { // 往右方走
                            nextRow = nextRow;
                            nextCol = nextCol + 1;
                        }
                        else {// 往下方走
                            nextRow = nextRow + 1;
                            nextCol = nextCol;
                        }
                    }
                    // 到达终点，回溯
                    if (nextRow == m-1 && nextCol == n-1) {
                        total++;
                        goOrBack = 0;
                    }
                }
                else { // 回溯
                    Grid &g = path.top();
                    if (g.way == BELOW) {// 如果上一步是向下走的，继续回溯
                        path.pop();
                        goOrBack = 0;
                        matrix[g.row][g.col] = 0;
                    }
                    else {// 否则
                        vector<int> ways = getWay(g.row, g.col, m, n);
                        if (ways.size() == 1) {// 只有一个方向的，继续回溯
                            path.pop();
                            goOrBack = 0;
                            matrix[g.row][g.col] = 0;
                        }
                        else { // 上次走的是右方，而且下方还可以尝试
                            g.way = BELOW;
                            goOrBack = 1;
                            nextRow = g.row + 1;
                            nextCol = g.col;
                        }
                    }

                }
            }
            else {
                if (m == 1 || n == 1) {
                    total++;
                }
                break;
            }
        }
        return total;
    }
};
```

按照这个方法是可以的，但是当m、n很大时，就超时了。