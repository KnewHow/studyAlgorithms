#pragma once
#include<string>
#include<unordered_map>

class Solution {
public:
    std::string minWindow(std::string s, std::string t);
    // �Ƚϴ����е��ַ����Ƿ����Ŀ���ַ����е������ַ�
    bool check(const std::unordered_map<char, int>& window, const std::unordered_map<char, int>& target);
};