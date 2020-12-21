#pragma once
#include<string>
#include<vector>

class Solution {
public:
    static constexpr int SEGMENT_TOTAL = 4;
    
    std::vector<std::string> restoreIpAddresses(std::string s);
    
    /**
    * ʹ�õݹ�ķ�ʽ������
    * @param s �����ַ���
    * @param res ��Ž������
    * @param temp ��ʱ�洢��IP��
    * @param currentSegment ��ǰ��Ҫ��ɵ�Ƭ��
    * @param startIndex �ַ���s�Ŀ�ʼ�Ǳ֮꣬ǰ���Ѿ����ù�
    */
    void doParse(const std::string& s, std::vector<std::string>& res, std::vector<std::string>& temp, int currentSegment, int startIndex);
};