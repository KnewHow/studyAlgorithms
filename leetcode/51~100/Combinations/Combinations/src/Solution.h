#pragma once
#include<vector>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k);
    
    /**
    * 递归的执行组合，每次将交换元素后的集合递归的执行
    * @param nums 1~n的数字集合，随之程序执行，顺序会被打乱
    * @param res 最终返回的结果
    * @param k k个元素的组合
    * @param nth 当前组合到第 nth 个元素
    */
    void doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int nth);
    /**
    * 根据角标交换集合中元素
    */
    void swap(std::vector<int>& v, int i, int j);
};