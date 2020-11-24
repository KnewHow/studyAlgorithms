#pragma once
#include<vector>
#include<set>
class Solution {
public:
    // copy original matrix
    void setZeroes(std::vector<std::vector<int>>& matrix);
    
    // use two set to store row and col needed clear zero
    void setZeroes2(std::vector<std::vector<int>>& matrix);

    // use 0 flag to implement O(1) space
    void setZeroes3(std::vector<std::vector<int>>& matrix);

    
};