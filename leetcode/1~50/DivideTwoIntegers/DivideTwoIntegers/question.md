# Divide Two Integers

Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when the division result overflows.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/divide-two-integers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：用减法

看到题目就想打死作者，不能用除法、乘法、取模，那我用减法，每次减去 `divisor`，但是会有溢出的问题，所以我们把`divident`和`dividor`都转换成负数。

```c
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

	int quotient = 0;
	while (dividend <= divisor)
	{
		dividend -= divisor;
		quotient--;
	}
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
```

但是这个方法效率不高，遇到 `dividor`比较小的就很慢。

## 解法二：用翻倍法

上面的减法方案速度太慢，我们至少需要循环`divident/divisor`次，如果`divident`太大而`divisor`太小，那么就会导致循环此时太多，导致速度过慢。参考网上的题解思路，找到一种翻倍法：https://leetcode-cn.com/problems/divide-two-integers/solution/po-su-de-xiang-fa-mei-you-wei-yun-suan-mei-you-yi-/。

我们可以换一种思路考虑，当`divident=12,divisor=2`,那么我们可以先让`divisor`翻倍，比较`(divisor + divisor) < divident`,如果是，让 `divisor=  divisor + divisor`，然后再翻倍比较，这样我们的增长值此时就不再是之前的每次`divisor`,而是`divisor * 2^m`,具体的代码如下：

```c
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
```

