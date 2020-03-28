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
            // 可以跳跃的最大角标，要求nums[maxEnableJumpIndex] !=0
            int maxEnableJumpIndex = 0;
            // 最大可以到达的角标
            int maxReachIndex = nums[0];
            int maxReachIndexBegin = 0;
            int i = 0;
            int begin = i;
            while (i < size) {
                int step = nums[i];
                if (maxReachIndex == i && maxEnableJumpIndex <= i && step == 0) {
                    return false;
                }
                if (i - begin <= nums[begin]) { // 还在上一步的跳跃范围中
                    int temp = i + nums[i];
                    if (temp >= size - 1) {
                        return true;
                    }
                    if (temp > maxReachIndex) {
                        maxReachIndex = temp;
                        maxReachIndexBegin = i;
                    }
                    if (temp > maxEnableJumpIndex && nums[temp] != 0) { // 判断最大可跳跃角标是否更新
                        maxEnableJumpIndex = i + nums[i];
                    }
                    i++;
                }
                else if(maxEnableJumpIndex!= begin && nums[maxEnableJumpIndex]!=0) { // 可以到达下一个最大的可以跳跃点
                    begin = maxEnableJumpIndex;
                    i = begin;
                    continue;
                }
                else { // 无法到达下一个可以跳跃的最大点，则我们让begin maxReachIndex 开始
                    begin = maxReachIndexBegin;
                }
                
            }
            return false;
        }
    }
};