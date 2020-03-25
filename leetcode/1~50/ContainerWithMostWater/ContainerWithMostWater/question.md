# Question

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

 ![](D:\project\studyAlgorithms\ContainerWithMostWater\ContainerWithMostWater\demo.png)



The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

 

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/container-with-most-water
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

## 解法一 暴力法

可以构建一个 n x n，矩阵，每次表示每个元素之间构成的最大面积，最后求得最大值。但是此算法的效率不高，时间复杂度为 `O(n^2)` 

```c
int minValue(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int maxArea(int* height, int heightSize) {
	int max = 0;
	for (int i = 0; i < heightSize; i++) {
		for (int j = i + 1; j < heightSize; j++) {
			int t = minValue(height[i], height[j]) * (j - i);
			if (t > max) {
				max = t;
			}
		}
	}
	return max;
}
```

## 解法二:双指针法

看了参考答案，原来这么简单，自己想半天也没想明白。

一头一尾由于 x 轴的距离最长，让其为初始值，然后我们需要找两个较大的值，使得他们两个高度可以弥补 x 轴的距离遍历，我们用两个指针分别指向一头一尾，如果头比尾大，尾--，否则头++，每次计算的 area 和 初始值比较，取较大的那个，知道头和尾遇到。代码如下：

```c
int minValue(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int maxAreaWithTwoPointer(int* height, int heightSize) {
	int* head = height;
	int* tail = height + heightSize - 1;
	int max = minValue(*head, *tail) * (tail - head);
	while (head < tail) {
		int t = minValue(*head, *tail) * (tail - head);
		if (t > max) {
			max = t;
		}
		if (*head > * tail) {
			tail--;
		}
		else {
			head++;
		}
	}
	return max;
}
```

时间复杂度为 `O(n)`