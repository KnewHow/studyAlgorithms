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
class Solution2 {
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