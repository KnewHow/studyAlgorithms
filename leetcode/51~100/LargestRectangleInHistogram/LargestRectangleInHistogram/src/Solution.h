#pragma once
#include<vector>
#include<stack>
class Solution {
public:
    int largestRectangleAreaOpt(std::vector<int>& heights);
    int largestRectangleArea(std::vector<int>& heights);
    int largestRectangleArea_Height(std::vector<int>& heights);
    int largestRectangleArea_Width(std::vector<int>& heights);
};