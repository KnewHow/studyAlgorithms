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