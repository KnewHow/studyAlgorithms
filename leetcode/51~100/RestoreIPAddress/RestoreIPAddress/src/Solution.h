#pragma once
#include<string>
#include<vector>

class Solution {
public:
    static constexpr int SEGMENT_TOTAL = 4;
    
    std::vector<std::string> restoreIpAddresses(std::string s);
    
    /**
    * 使用递归的方式来解析
    * @param s 给定字符串
    * @param res 存放结果集合
    * @param temp 临时存储的IP段
    * @param currentSegment 当前需要完成的片段
    * @param startIndex 字符串s的开始角标，之前的已经被用过
    */
    void doParse(const std::string& s, std::vector<std::string>& res, std::vector<std::string>& temp, int currentSegment, int startIndex);
};