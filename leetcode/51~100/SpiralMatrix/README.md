# Question

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

```
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
```


Example 2:

```
Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/spiral-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

设矩阵为`m x n`的大小，由于每次螺旋后，矩阵就变为`m-2 x n-2`的更小矩阵，然后再次螺旋即可。

```c++
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row = matrix.size();
        vector<int> r = vector<int>();
        if (row == 0) {
            return r;
        }
        else {
            vector<int> first = matrix.front();
            int col = first.size();
            int begin = 0;
            while (row > 0 && col > 0) {
                doSpiral(matrix, begin, begin, row, col, r);
                begin++;
                row -= 2;
                col -= 2;
            }
            return r;
        }
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
    void doSpiral(vector<vector<int>>& matrix, int beginRow, int beginCol, int row, int col, vector<int>& r) {
        //第一行
        for (int i = beginCol; i < beginCol + col; i++) {
            int v = matrix[beginRow][i];
            r.push_back(v);
        }
        // 最后一列,但是排除第一个元素
        int lastColNumber = beginCol + col - 1;
        for (int i = beginRow + 1; i < beginRow + row; i++) {
            int v = matrix[i][lastColNumber];
            r.push_back(v);
        }
        // 最后一行，但是排除最后一个元素
        int lastRowNumber = beginRow + row - 1;
        if (row > 1) { // 当row > 1的时候才执行，最后一行和第一行才不会重复
            for (int i = lastColNumber - 1; i >= beginCol; i--) {
                int v = matrix[lastRowNumber][i];
                r.push_back(v);
            }
        }
        if (col > 1) { // 当 col > 1，第一列和最后一列才不会重复
            // 第一列，但排除最后一个元素和第一个元素
            for (int i = lastRowNumber - 1; i > beginRow; i--) {
                int v = matrix[i][beginCol];
                r.push_back(v);
            }
        }
        
    }
};
```



