#pragma once

#include<vector>
class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums);

    /**
    * 递归的执行组合，每次将交换元素后的集合递归的执行
    * @param nums 1~n的数字集合，随之程序执行，顺序会被打乱
    * @param res 最终返回的结果
    * @param k k个元素的组合
    * @param previousIndex 上一个元素取的角标
    * @param nth 当前组合到第 kth 个元素
    * @param tmp 之前已经保存的结果，这里使用引用会减少多次复制
    */
    void doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp);

};