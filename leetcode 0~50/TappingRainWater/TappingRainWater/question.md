# Trapping Rain Water

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

![](rainwatertrap.png)


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/trapping-rain-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

从第一个非0的高度`i`开始，往后面找到一个高度`j`,使得`j >=i`,然后计算`i~j`之间可以存储雨水的体积。但是当`i = 3`，到后面还没找到比`i`大的高度数组就结束了，这么办呢？此时我们可以反过来，从数组的末尾高度不为0的数开始，一直找到之前的`iMax`。

代码如下：

```c
#include<stdio.h>
#include<stdlib.h>

int clcWater(int* height, int begin, int end) {
	if (end - begin > 1) { // 只有间距大于 1 才计算
		// 找出两高度的最小值作为高
		int v1 = *(height + begin);
		int v2 = *(height + end);
		int v = min(v1, v2);
		int total = v * (end - begin + 1);
		// 减去实心部分，如果高度超过了，以最小高度为准
		for (int i = begin; i <= end; i++) {
			int h = *(height + i);
			if (h > v) {
				h = v;
			}
			total -= h;
		}
		return total;
	}
	else {
		return 0;
	}
}

int trap(int* height, int heightSize) {
	if (heightSize <= 1) {
		return 0;
	}
	else {
		int sum = 0;
		int i = 0;
		// 从第一个不为0的开始
		while (i < heightSize) {
			if (*(height + i) == 0) {
				i++;
			}
			else {
				break;
			}
		}
		int beginIndex = i;
		int begin = *(height + i);
		i++;
		for (; i < heightSize; i++) {
			if (*(height + i) >= begin) {
				sum += clcWater(height, beginIndex, i);
				begin = *(height + i);
				beginIndex = i;
			}
		}
		// 如果循环结果， begin 应该是数组中最大值了，我们需要从右往左推一遍
		// 找出因 begin 太高而漏掉的部分
		int max = begin;
		int maxIndex = beginIndex;
		i = heightSize - 1;
		while (i > maxIndex) {
			if (*(height + i) == 0) {
				i--;
			}
			else {
				break;
			}
		}
		begin = *(height + i);
		beginIndex = i;
		i--;
		for (; i >= maxIndex; i--) {
			if (*(height + i) >= begin) {
				sum += clcWater(height, i, beginIndex);
				begin = *(height + i);
				beginIndex = i;
			}
		}
		return sum;
	}
}

int main() {
	int height[] = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	int size = sizeof(height) / sizeof(int);
	int sum = trap(height, size);
	printf("sum is:%d\n", sum);
	system("pause");
	return 0;
}
```

时间复杂度为 `O(N)`