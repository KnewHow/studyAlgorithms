#pragma once
#include<vector>
#include<unordered_set>
#include<algorithm>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

using MySet = std::unordered_set<std::vector<int>, VectorHash>;

class Solution {
public:
    
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);
    void doCombine_DeleteRepeat(const std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp);
  
    std::vector<std::vector<int>> subsetsWithDup_WithOuter(std::vector<int>& nums);
    void doCombine(std::vector<int>& nums, MySet& res, int k, int previousIndex, int kth, std::vector<int>& tmp);
};