#pragma once
#include<string>
#include<unordered_map>

class Solution {
public:
    int numDecodings(std::string s);

    int doDecoding(const std::string& s, std::unordered_map<std::string, int>& dp);
};