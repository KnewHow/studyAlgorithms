#pragma once
#include<string>
#include<unordered_map>

class Solution {
public:
    std::string minWindow(std::string s, std::string t);
    // 比较窗口中的字符串是否包含目标字符串中的所有字符
    bool check(const std::unordered_map<char, int>& window, const std::unordered_map<char, int>& target);
};