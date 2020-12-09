#include "Solution.h"

int Solution::largestRectangleAreaOpt(std::vector<int>& heights)
{
    int n = heights.size();
    std::vector<int> left(n), right(n,n);
    std::stack<int> stack;
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
        res = std::max(res, heights[i] * (right[i] - left[i] - 1));
    }
    return res;
}

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

int Solution::largestRectangleArea_Height(std::vector<int>& heights)
{
    int res = 0;
    for (int i = 0; i < heights.size(); i++) {
        int mid = i;
        int height = heights[mid];
        int left = mid;
        int right = mid;
        while (left - 1 >= 0 && heights[left - 1] >= height) {
            left--;
        }

        while (right + 1 < heights.size() && heights[right + 1] >= height) {
            right++;
        }

        res = std::max(res, height * (right - left + 1));

    }
    return res;
}

int Solution::largestRectangleArea_Width(std::vector<int>& heights)
{
    int res = 0;
    for (int left = 0; left < heights.size(); left++) {
        int height = heights[left];
        for (int right = left; right < heights.size(); right++) {
            height = std::min(height, heights[right]);
            res = std::max(res, height * (right - left + 1));
        }
    }
    return res;
}
