# Question

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.
Example 1:

Input: "42"
Output: 42
Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/string-to-integer-atoi
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

判断原字符串和合法性，如果不合法直接返回 0，否则转换为整数，如果上溢出，返回 `INT_MAX`，下溢出返回 `INT_MIN`	

```c
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

/**
* 根据原始字符串提取数字，其中第一个字符表示数字的 + 或者是 -
* 根据题目的要求，忽略字符串的空格，第一个非空格的字符若是 '+' 、 '-'或是数字则为合法字符
* 我们需要将这些字符转换为整数
*/
char* getNumber(char* str) {
	char* nums = (char*)malloc(sizeof(char) * 1024);
	char* p = str;
	int size = 0;
	while (*p != '\0') {
		if (*p == '+' || *p == '-') {
			if (size == 0) { // 遇到正负号的时候，size 必须是0，否则忽略后面的，跳出循环
				nums[size++] = *p; 
			}
			else {
				break;
			}
		}
		else if (*p == ' ') {
			if (size != 0) { // 如果在已经存储数字后遇到空格，则中断循环
				break;
			}
		}
		else if (*p >= '0' && *p <= '9') {
			if (size == 0) { // 如果遇到第一个数字，但是 size 还是为 0，表示是个正数
				nums[size++] = '+';
			}
			nums[size++] = *p;
		}
		else {// 其他字符
			// 当遇到其它字符时，如果size ==0，表示以其它字符开始，atoi 应该返回 0
			if (size == 0) {
				free(nums);
				nums = NULL;
			}
			break;
		}
		p++;
	}
	if (size == 0) { // 空字符串
		return NULL;
	} else if (nums == NULL) {// 无效的字符串
		return NULL;
	} else {
		nums[size] = '\0'; // 字符串结束标识
		return nums;
	}
}

/**
* 将一个字符串整数字符串转换为数字整数
*/
int myAtoi(char* str) {
	char* numbers = getNumber(str);
	if (numbers == NULL) {
		return 0;
	}
	else {
		long long num = 0;
		char* p = numbers;
		long long sign = 1;
		if (*p == '-') {
			sign = -1;
		}
		p++;
		while (*p != '\0') {
			int n = *p - 48; // 将字符数字转换为整型数字
			num = num * 10 + n;
			if (sign == 1 && num > INT_MAX) { // 如果溢出，直接返回 int 极值
				return INT_MAX;
			}
			if (sign == -1 && (num * sign) < INT_MIN) {
				return INT_MIN;
			}
			p++;
		}
		return num * sign;
	}
}

int main() {
	int r = myAtoi("-5-");
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}
```

