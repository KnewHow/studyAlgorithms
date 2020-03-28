# Question

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

Example 1:

```
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```


Example 2:

```
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

按照[45. Jump Game II](https://leetcode-cn.com/problems/jump-game-ii/)的思路，但是这里不能完全照搬，因为有些情况下，可达的最大点`maxEnableJumpIndex`可能是个无法跳跃的陷阱，因此只有当最大点可跳跃的时候，我们才更新他的值，但是我们增加一个辅助变量`maxReachIndex`, 表示可以达到的最远角标，当`maxEnableJumpIndex`无法确定时候，利用`maxReachIndex`来继续前进。代码如下：

```c++
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
```

