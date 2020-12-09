#pragma once
#include<string>
#include<vector>
#include<unordered_map>
class Solution {
public:

    bool isScramble(std::string s1, std::string s2);
    bool doScramble(std::string s1, std::string s2, std::unordered_map<std::string, int> dp);

    bool isScramble2(std::string s1, std::string s2);
};