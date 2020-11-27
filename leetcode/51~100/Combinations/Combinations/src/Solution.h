#pragma once
#include<vector>

class Solution {
public:
    std::vector<std::vector<int>> combine(int n, int k);
    
    /**
    * �ݹ��ִ����ϣ�ÿ�ν�����Ԫ�غ�ļ��ϵݹ��ִ��
    * @param nums 1~n�����ּ��ϣ���֮����ִ�У�˳��ᱻ����
    * @param res ���շ��صĽ��
    * @param k k��Ԫ�ص����
    * @param nth ��ǰ��ϵ��� nth ��Ԫ��
    */
    void doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int nth);
    /**
    * ���ݽǱ꽻��������Ԫ��
    */
    void swap(std::vector<int>& v, int i, int j);
};