#pragma once
#include<string>
#include<unordered_map>

class Solution {
public:
    std::string minWindow(std::string s, std::string t);


    /** 
    * 与上面的算法相比，原理差不多，
    * 只是增加了一个counter 变量来记录长度，
    * 避免了重复且耗时比较操作，效率提升了不少 
    */
    std::string minWindow2(std::string s, std::string t);

    /* 
    * 由于字符串都是字母，字符的个数是固定的，
    * 在上面算法的基础上，使用原生数组代替unordered_map,
    * 减少花费在map搜索上的开销，
    * 将搜索时间复杂的变为恒定的0(1)，减少整个算法的开销
    */
    std::string minWindow3(std::string s, std::string t);
    
    /**
    * 比较窗口中的字符串是否包含目标字符串中的所有字符 
    */
    bool check(const std::unordered_map<char, int>& window, const std::unordered_map<char, int>& target);
};