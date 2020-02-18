# Question

Given an array nums of n integers and an integer target, find three integers in nums such that the sum is closest to target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：暴力法

直接算法原数组中所有三个元素之和，比较他们和`target`的距离，取距离最小的，此算法的时间复杂度为`O(N^3)`

```c
int threeSumClosest(int* nums, int numsSize, int target){
    int distans = INT_MAX;
	int sum = 0;
	for (int x = 0; x < numsSize; x++) {
		for (int y = x + 1; y < numsSize; y++) {
			for (int z = y + 1; z < numsSize; z++) {
				int s = nums[x] + nums[y] + nums[z];
				int dis = abs(target - s);
				if (dis < distans) {
					distans = dis;
					sum = s;
				}
			}
		}
	}
	return sum;
}
```

没有超时，竟然通过了，刺激。



## 解法二： 利用两数之和和二分查找

我们还是可以使用两数之和的算法，设当前元素为三个元素中的其中一个元素为`x`，然后找两个数，使他们之和离`target-x`最近，我们可以利用二分查找，如果找到该元素，则已经有最小的，为0，如果找不到，二分查找可以帮我定位距离目标元素最近的元素，把他返回，用来比较，此算法的时间复杂度为`O(n^2lgN)`