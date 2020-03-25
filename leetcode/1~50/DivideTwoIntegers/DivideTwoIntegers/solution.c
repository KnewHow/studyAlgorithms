#include<stdlib.h>
#include<stdio.h>

int divR(int divident, int divisor) {
	if (divident > divisor) {
		return 0;
	}
	else {
		// 计数器，初始化为-1，避免数据溢出
		int counter = -1;
		// 这里对 tb 使用 long long 类型，不然可能会造成数据的溢出
		long long int tb = divisor;
		while ((tb + tb) > divident) {
			// 每次让 counter 和 divisor 翻倍，如果 divident = -12 dividor=-2
			// 我们只需要翻倍 4 次就可，比原来每次翻一次快了很多
			// 以 divisor * 2^n 的速度在增长
			counter = counter + counter;
			tb = tb + tb;
		}
		return counter + divR(divident - tb, divisor);
	}
}

int divide(int dividend, int divisor) {
	// -1 和 +1 做特殊处理
	if (divisor == 1) {
		return dividend;
	}
	if (divisor == -1) {
		if (dividend == INT_MIN) {
			return INT_MAX;
		}
		else {
			return -dividend;
		}
	}
	// 符号标志位，同号为1，异号为-1
	int tag = 1;
	if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0)) {
		tag = 1;
	}
	else {
		tag = -1;
	}

	// 全部化成负数计算，因为负数不会产生溢出
	if (dividend > 0) {
		dividend = -dividend;
	}
	if (divisor > 0) {
		divisor = -divisor;
	}

	int quotient = divR(dividend, divisor);
	if (tag == -1) {
		return quotient;
	}
	else {
		if (quotient <= INT_MIN) {
			return INT_MAX;
		}
		else {
			return -quotient;
		}
	}
}

int main() {
	int dividend = 2147483647;
	int divisor = 3;
	int quotient = divide(dividend, divisor);
	printf("quotient is %d\n", quotient);
	system("pause");
	return 0;
}