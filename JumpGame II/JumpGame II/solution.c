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

int main() {
	int nums[] = { 2,3,1,1,4 };
	int size = sizeof(nums) / sizeof(int);
	int r = jump2(nums, size);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}