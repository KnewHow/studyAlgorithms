#pragma once
#include<string>
#include<unordered_map>

class Solution {
public:
    std::string minWindow(std::string s, std::string t);


    /** 
    * ��������㷨��ȣ�ԭ���࣬
    * ֻ��������һ��counter ��������¼���ȣ�
    * �������ظ��Һ�ʱ�Ƚϲ�����Ч�������˲��� 
    */
    std::string minWindow2(std::string s, std::string t);

    /* 
    * �����ַ���������ĸ���ַ��ĸ����ǹ̶��ģ�
    * �������㷨�Ļ����ϣ�ʹ��ԭ���������unordered_map,
    * ���ٻ�����map�����ϵĿ�����
    * ������ʱ�临�ӵı�Ϊ�㶨��0(1)�����������㷨�Ŀ���
    */
    std::string minWindow3(std::string s, std::string t);
    
    /**
    * �Ƚϴ����е��ַ����Ƿ����Ŀ���ַ����е������ַ� 
    */
    bool check(const std::unordered_map<char, int>& window, const std::unordered_map<char, int>& target);
};