#include<vector>
using namespace std;

class Solution {
public:
    /**
    * ���������Լ�����ÿ��Ԫ������������кͣ�����ȵ�ǰ�� maxSun �󣬸��� maxSum��ֵ
    * ʱ�临�Ӷ�ΪO(n^2)
    */
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if (sum > maxSum) {
                    maxSum = sum;
                }
            }
           
       }
        return maxSum;
    }

    /**
    * ��һ�� currentMaxSum ���洢��ǰ�����кͣ���� currentMaxSum > maxSum,
    * ���� maxSum��ֵ��
    * ��� currentMaxSum < 0,��ʾ����Ժ�������к���ɼ�С��Ӱ�죬ֱ������Ϊ0
    * ���ʱ�临�Ӷ�ΪO(n)
    */
    int maxSubArray_2(vector<int>& nums) {
        int maxSum = INT_MIN;
        int currentMaxSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            currentMaxSum = currentMaxSum + nums[i];
            if (currentMaxSum > maxSum) {
                maxSum = currentMaxSum;
            }
            // currentMaxSum С��0ʱ����Ժ���Ĳ�����СӰ�죬Ӧ��ȥ
            if (currentMaxSum < 0) {
                currentMaxSum = 0;
            }

        }
        return maxSum;
    }
};