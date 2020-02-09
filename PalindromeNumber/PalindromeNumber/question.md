# Question

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true
Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
Follow up:

Coud you solve it without converting the integer to a string?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

如果是负数，肯定不是回文数，回文数的特点是位置互换后，值仍然相等，因此我们把原数的每位数字计算出来，反转，然后转换为十进制数，判断和原来的数是否相等。

```c
int isPalindrome(int x) {
	if (x < 0) { // 负数不可能为回文数
		return 0;
	}
	else {
		int a[1024] = { 0 };
		int size = 0;
		long long int num = x;
		while (num != 0) {
			a[size++] = num % 10;
			num = num / 10;
		}
		long long int newNum = 0;
		for (int i = 0; i < size; i++) {
			newNum = newNum * 10 + a[i];
			// 如果超出 INT_MAX 不可能为回文数
			if (newNum > INT_MAX) {
				return 0;
			}
		}
		return x == newNum;
	}
}

int main() {
	int x = 2147483647;
	int r = isPalindrome(x);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}
```

