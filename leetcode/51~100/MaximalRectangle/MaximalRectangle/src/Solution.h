#pragma once
#include<vector>
#include<stack>

class Solution {
public:
    /**
    * 利用柱状图使问题简化
    */
    int maximalRectangle(std::vector<std::vector<char>>& matrix);

    int getMaxRectangleInHistogram(const std::vector<int>& heights);
};