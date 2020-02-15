# Question

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"
Example 2:

Input: 4
Output: "IV"
Example 3:

Input: 9
Output: "IX"
Example 4:

Input: 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.
Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/integer-to-roman
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

由于罗马的数字是有限的，因此我们可以分类来讨论。首先我们需要获取给定数字的个位、十位、百位、千位分别是多少，然后算出对应的字符串，最后拼接在一起返回。

```c
#include<stdlib.h>
#include<stdio.h>

void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}

/**
* 根据数字来获取罗马字符串，根据传入的字符串来确定数字到底是个位、十位还是百位
* @param num 给定的数字，范围在 1-9 之间
* @param  one 10^k 的字符，1-I, 10-X, 100-C
* @param five 5*10^k 的字符， 5-V, 50-L, 500-D
* @return 用来表示数字的罗马字符串
*/
char* getRoman(int num, char one, char five, char ten) {
	char* str = (char*)malloc(5 * sizeof(char));
	int size = 0;
	switch (num)
	{
	case 0:
		break;
	case 1:
		str[size++] = one;
		break;
	case 2:
		str[size++] = one;
		str[size++] = one;
		break;
	case 3:
		str[size++] = one;
		str[size++] = one;
		str[size++] = one;
		break;
	case 4:
		str[size++] = one;
		str[size++] = five;
		break;
	case 5:
		str[size++] = five;
		break;
	case 6:
		str[size++] = five;
		str[size++] = one;
		break;
	case 7:
		str[size++] = five;
		str[size++] = one;
		str[size++] = one;
		break;
	case 8:
		str[size++] = five;
		str[size++] = one;
		str[size++] = one;
		str[size++] = one;
		break;
	case 9:
		str[size++] = one;
		str[size++] = ten;
		break;

	default:
		break;
	}
	str[size++] = '\0';
	return str;
}

int getSize(char* str) {
	int size = 0;
	while (str[size] != '\0') {
		size++;
	}
	return size;
}

void concatStr(char* s1, char* s2) {
	int size = getSize(s1);
	char* tail = s1 + size;
	char* p = s2;
	while (*p != '\0') {
		*tail = *p;
		p++;
		tail++;
	}
	*tail = '\0';
}


char* intToRoman(int num) {
	int arr[10] = { 0 };
	// 获取num 各位数字
	int n = num;
	int size = 0;
	while (n > 0) {
		arr[size++] = n % 10;
		n = n / 10;
	}
	char* romanStr = (char*)malloc(1024 * sizeof(char));
	*romanStr = '\0';
	int rSize = 0;
	char* r = NULL;
	// 倒序，从最高位算起
	for (int i = size - 1; i >= 0; i--) {
		switch (i)
		{
		case 0: // 个位
			r = getRoman(arr[i], 'I', 'V', 'X');
			concatStr(romanStr, r);
			break;
		case 1: // 十位
			r = getRoman(arr[i], 'X', 'L', 'C');
			concatStr(romanStr, r);
			break;
		case 2: // 百位
			r = getRoman(arr[i], 'C', 'D', 'M');
			concatStr(romanStr, r);
			break;
		case 3: // 千位,由于不超过 3000，则后面两位使用 \0 代替
			r = getRoman(arr[i], 'M', '\0', '\0');
			concatStr(romanStr, r);
			break;
		default:
			break;
		}
		// 回收 r
		if (r != NULL) {
			free(r);
		}
	}
	return romanStr;
}

int main() {
	char * r = intToRoman(3999);
	printf("roman number is:%s", r);
	free(r);
	system("pause");
	return 0;
}
```

