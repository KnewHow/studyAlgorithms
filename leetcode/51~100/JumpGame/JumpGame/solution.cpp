#include<vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        if (size == 0) {
            return false;
        }
        else if (size == 1) {
            return true;
        }
        else {
            // ������Ծ�����Ǳ꣬Ҫ��nums[maxEnableJumpIndex] !=0
            int maxEnableJumpIndex = 0;
            // �����Ե���ĽǱ�
            int maxReachIndex = nums[0];
            int maxReachIndexBegin = 0;
            int i = 0;
            int begin = i;
            while (i < size) {
                int step = nums[i];
                if (maxReachIndex == i && maxEnableJumpIndex <= i && step == 0) {
                    return false;
                }
                if (i - begin <= nums[begin]) { // ������һ������Ծ��Χ��
                    int temp = i + nums[i];
                    if (temp >= size - 1) {
                        return true;
                    }
                    if (temp > maxReachIndex) {
                        maxReachIndex = temp;
                        maxReachIndexBegin = i;
                    }
                    if (temp > maxEnableJumpIndex && nums[temp] != 0) { // �ж�������Ծ�Ǳ��Ƿ����
                        maxEnableJumpIndex = i + nums[i];
                    }
                    i++;
                }
                else if(maxEnableJumpIndex!= begin && nums[maxEnableJumpIndex]!=0) { // ���Ե�����һ�����Ŀ�����Ծ��
                    begin = maxEnableJumpIndex;
                    i = begin;
                    continue;
                }
                else { // �޷�������һ��������Ծ�����㣬��������begin maxReachIndex ��ʼ
                    begin = maxReachIndexBegin;
                }
                
            }
            return false;
        }
    }
};