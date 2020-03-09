# Jump Game II

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

Example:

Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
    Jump 1 step from index 0 to 1, then 3 steps to the last index.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：递归解决子问题

当我们走到第`i` 个 position 时，我们有能力跳跃`arr[i]`步，让 `j 1-arr[i]`,递归的解决问题。

```c
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/**
* 返回当前点到终点的最小距离
* @param nums 原数组
* @param numsSize 原数组大小
* @param position 当前位置
* @param steps 当前已经走了多少步
* @param minSteps 与原数组中相对应，反应每个位置到终点的最小步数，为了优化递归的重复计算
* @returnMinStep 从起点到终点的最小步数的指针
* @return 从当前位置到终点的最小步数
*/
int go(int *nums, int numsSize, int position, int steps,  int *minSteps) {
	// 到达终点
	if (position == numsSize - 1) {
		return 0;
	}
	else { // 还没到
		// 之前已经计算过
		if (*(minSteps + position) != 0) {
			return *(minSteps + position);
		}
		else {
			int range = *(nums + position);
			int min = INT_MAX;
			for (int j = 1; j <= range; j++) {
				if (position + j <= numsSize - 1) {
					int r = go(nums, numsSize, position + j, steps + 1, minSteps);
					// 如果返回 INT_MAX  说明此路不通
					if (r == INT_MAX) {
						continue;
					}
					if (r + 1 < min) {
						min = r + 1;
					}
				}
			}
			*(minSteps + position) = min;
			return min;
		}
	}
}

int jump(int* nums, int numsSize) {
	// 一个数组，存储当前位置到终点的最小距离，初始化为0，每次递归后记忆
	int* minSteps = (int*)malloc(sizeof(int) * numsSize);
	for (int i = 0; i < numsSize; i++) {
		*(minSteps + i) = 0;
	}
	int r = go(nums, numsSize, 0, 0, minSteps);
	free(minSteps);
	return r;
}

int main() {
	int nums[] = { 2,3,1,1,4 };
	int size = sizeof(nums) / sizeof(int);
	int r = jump(nums, size);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}
```

代码应该没什么问题，但是对应下面这个测试用例，，数据量太大， stack overflow。

https://leetcode-cn.com/submissions/detail/52321679/testcase/

## 解法二：顺藤摸瓜

参考了[官方推荐的题解](https://leetcode-cn.com/problems/jump-game-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-10/),虽然题解一代码挺简单的，但不是那么好理解，下面是我给代码加的注释

```c
/**
* 顺藤摸瓜(贪心算法)
*/
int jump2(int* nums, int numsSize) {
	int steps = 0;
	int end = 0;
	int maxPosition = 0;
	// 因为终点是 numsSize-1,自己跳到自己上面需要0步，所以不需要计算
	for (int i = 0; i < numsSize - 1; i++) {
		// 每次记录从当前位置可以跳跃的最远位置，并记录下来
		maxPosition = max(maxPosition, nums[i] + i);
		/**
		* 初始的情况，当 end = 0 时，可以理解为首先要跳出第一步
		* 而当 end == i 时候，表示要到达当前的 maxPosition,需要在原来的基础上，再跳一步。
		*/
		if (end == i) {
			end = maxPosition;
			steps++;
		}
	}
	return steps;
}
```

 时间复杂度为`O(N)`，建议大家自己在草稿纸上推理一遍，就差不多会了。