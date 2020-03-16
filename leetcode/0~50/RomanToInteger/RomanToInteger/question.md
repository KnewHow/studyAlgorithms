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
Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3
Example 2:

Input: "IV"
Output: 4
Example 3:

Input: "IX"
Output: 9
Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/roman-to-integer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

我们用两个指针分别指向字符串的head和head的下一个，如果下一个数比当前的小，说明是正常顺序，是的当前的和与当前head指针的数相加，然后指针后移，否则让 head 和 next 做减法运算，然后让和加上运算的结果，然后指针往后移动两位，跳过这两个数。

```c
#include<stdio.h>
#include<stdlib.h>

// hashTable 为了读取数据方便，index 为罗马数字对应的 ASCII 值，
// value 是对应的整数值
int hashTable[1024] = { 0 };

void put(char c, int value) {
	int index = c;
	hashTable[index] = value;
}

int get(char c) {
	int index = c;
	return hashTable[index];
}

// 对hashTable 初始化
void initHashTable() {
	char cs[] = { 'I','V','X','L','C','D','M' };
	int  vs[] = {1,5,10,50,100,500,1000};
	for (int i = 0; i < sizeof(cs) / sizeof(char); i++) {
		put(cs[i], vs[i]);
	}
}

// c1 的罗马数字是否比 c2 的罗马数字大
// 1-是 0-否
int isGreater(char c1, char c2) {
	if (get(c1) > get(c2)) {
		return 1;
	}
	else {
		return 0;
	}
}

int romanToInt(char* s) {
	initHashTable();
	char* head = s;
	char* next = head + 1;
	int sum = 0;
	while (*head != '\0' && *next != '\0') {
		// 后一个比前一个大,表示减法运算
		if (isGreater(*next, *head)) {
			int v1 = get(*next);
			int v2 = get(*head);
			int v = v1 - v2;
			sum += v;
			head += 2;
			next += 2;
		}
		else { // 正常叠加
			int v = get(*head);
			sum += v;
			head++;
			next++;
		}
	}
	// 防止 *next 为空导致漏掉最后一个数字
	if (*head != '\0') {
		int v = get(*head);
		sum += v;
	}
	return sum;
}

int main() {
	char arr[] = "MCMXCIV";
	int num = romanToInt(arr);
	printf("roman:%s to number is:%d\n", arr, num);
	system("pause");
	return 0;
}
```

