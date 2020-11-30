#pragma once

#include<vector>
class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums);

    /**
    * �ݹ��ִ����ϣ�ÿ�ν�����Ԫ�غ�ļ��ϵݹ��ִ��
    * @param nums 1~n�����ּ��ϣ���֮����ִ�У�˳��ᱻ����
    * @param res ���շ��صĽ��
    * @param k k��Ԫ�ص����
    * @param previousIndex ��һ��Ԫ��ȡ�ĽǱ�
    * @param nth ��ǰ��ϵ��� kth ��Ԫ��
    * @param tmp ֮ǰ�Ѿ�����Ľ��������ʹ�����û���ٶ�θ���
    */
    void doCombine(std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp);

};