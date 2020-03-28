# Question

Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

## 解法一：暴力法

```c++
    /**
    * 暴力法：对集合中每个元素向后求其子列和，如果比当前的 maxSun 大，更新 maxSum的值
    * 时间复杂度为(On^2)
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

```

## 解法二：一边遍历法

```c++
/**
    * 用一个 currentMaxSum 来存储当前的子列和，如果 currentMaxSum > maxSum,
    * 更新 maxSum的值。
    * 如果 currentMaxSum < 0,表示他会对后面的序列和造成减小的影响，直接重置为0
    * 因此时间复杂度为O(n)
    */
    int maxSubArray_2(vector<int>& nums) {
        int maxSum = INT_MIN;
        int currentMaxSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            currentMaxSum = currentMaxSum + nums[i];
            if (currentMaxSum > maxSum) {
                maxSum = currentMaxSum;
            }
            // currentMaxSum 小于0时，会对后面的产生减小影响，应舍去
            if (currentMaxSum < 0) {
                currentMaxSum = 0;
            }

        }
        return maxSum;
    }
```

