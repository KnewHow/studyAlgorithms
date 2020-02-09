# Question

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
Note:
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-integer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Answer

将该数逐级和 10 取模，求取每一位，用链表进行封装，使用数组进行组装，然后查找尾元素第一个不为0的数，在反算成十进制数。如果数值溢出，则返回0

```c
int reverse(int x) {
	long long int nums[20] = { 0 };
	int length = 0;
	while (x != 0) {
		int r = x % 10;
		nums[length] = r;
		length++;
		x = x / 10;
	}
	long long int sum = 0;
	for (int i = 0; i < length; i++) {
		sum = nums[i] + sum * 10;
	}
	if (sum > INT_MAX || sum < INT_MIN) {
		return 0;
	}
	else {
		return sum;
	}
}

int main() {
	int num = -321;
	long int r = reverse(num);
	printf("reverse result=%d\n", r);
	system("pause");
	return 0;
}
```

