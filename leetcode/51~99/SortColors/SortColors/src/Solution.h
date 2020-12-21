#pragma once
#include<vector>
#include<algorithm>

class Solution {
public:
    // use std::sort function
    void sortColors(std::vector<int>& nums);

    // use std::sort and Lambda
    void sortColors2(std::vector<int>& nums);

    // use costom quick algorithm
    void sortColors3(std::vector<int>& nums);

    // 使用统计算法,所谓的一遍遍历法
    void sortColors4(std::vector<int>& nums);
private:
    void quickSort(std::vector<int>& nums);
    void quickSortR(std::vector<int>& nums, int left, int right);
};