#  [Largest Rectangle in Histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)



Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

 ![](https://assets.leetcode.com/uploads/2018/10/12/histogram.png)


Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].

 

# ![](https://assets.leetcode.com/uploads/2018/10/12/histogram_area.png)


The largest rectangle is shown in the shaded area, which has area = 10 unit.

 

Example:

Input: [2,1,5,6,2,3]
Output: 10

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-rectangle-in-histogram
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## s1: 穷举法

我们可以列出所有给出元素的组合，但这方法似乎有些笨了，万一元素个数超过100个，效率极低。

## s2 宽度枚举和高度枚举

我们先固定左边柱子不动，然后依次向右遍历，计算面积，取最大值。

## s3 递增栈

官方题解给的递增栈：https://leetcode-cn.com/problems/largest-rectangle-in-histogram/solution/zhu-zhuang-tu-zhong-zui-da-de-ju-xing-by-leetcode-/

```c++
int Solution::largestRectangleArea(std::vector<int>& heights)
{
    int n = heights.size();
    std::stack<int> stack;
    std::vector<int> left(n), right(n);

    for (int i = 0; i < n; i++) { // find Ith last left who less it
        while (!stack.empty() && heights[stack.top()] >= heights[i]) {
            stack.pop();
        }
        left[i] = stack.empty() ? -1 : stack.top();
        stack.push(i);
    }

    stack = std::stack<int>();

    for (int i = n - 1; i >= 0; i--) {// find Ith last right who less it
        while (!stack.empty() && heights[stack.top()] >= heights[i]) {
            stack.pop();
        }
        right[i] = stack.empty() ? n : stack.top();
        stack.push(i);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        res = std::max(res, (right[i] - left[i] - 1) * heights[i]);
    }
    
    return res;
}
```

