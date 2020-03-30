# Question

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

```
Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/spiral-matrix-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

按照之前[54. Spiral Matrix](https://github.com/KnewHow/studyAlgorithms/tree/master/leetcode/51~100/SpiralMatrix)的思路，先初始化一个`n x n`的矩阵，然后再螺旋赋值，代码如下：

```c++
#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix = vector<vector<int>>();
        for (int i = 0; i < n; i++) {
            vector<int> row = vector<int>();
            for (int j = 0; j < n; j++) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
        int begin = 0;
        int row = n;
        int col = n;
        int current = 1;
        while (row > 0 && col > 0) {
            doSpiral(matrix, begin, begin, row, col, current);
            begin++;
            row -= 2;
            col -= 2;
        }
        return matrix;
    }
    /**
    * 对矩阵进行螺旋
    * @param matrix 原先的矩阵
    * @param beginRow 开始行
    * @param beginCol 开始列
    * @param 矩阵的 row 的长度
    * @param 矩阵的 col 的长度
    * @param r 最终的结果
    */
    void doSpiral(vector<vector<int>>& matrix, int beginRow, int beginCol, int row, int col, int &current) {
        //第一行
        for (int i = beginCol; i < beginCol + col; i++) {
            matrix[beginRow][i] = current++;
        }
        // 最后一列,但是排除第一个元素
        int lastColNumber = beginCol + col - 1;
        for (int i = beginRow + 1; i < beginRow + row; i++) {
            matrix[i][lastColNumber] = current++;
        }
        // 最后一行，但是排除最后一个元素
        int lastRowNumber = beginRow + row - 1;
        if (row > 1) { // 当row > 1的时候才执行，最后一行和第一行才不会重复
            for (int i = lastColNumber - 1; i >= beginCol; i--) {
               matrix[lastRowNumber][i] = current++;
            }
        }
        if (col > 1) { // 当 col > 1，第一列和最后一列才不会重复
            // 第一列，但排除最后一个元素和第一个元素
            for (int i = lastRowNumber - 1; i > beginRow; i--) {
                matrix[i][beginCol] = current++;
            }
        }

    }
};
```

