# Implement strStr()

Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：暴力法

如果`needle `是空字符串，则直接返回0，否则遍历`haystack `，然后判断是否存在`needle`，代码如下：

```c
int strStr(char * haystack, char * needle){
    // 如果 needle 为空字符，直接返回 0
	if (*needle == '\0') {
		return 0;
	}
	else {
		char* p = haystack;
		while (*p != '\0') {
			if (*p == *needle) { // 第一个匹配上了
				// 记住开始的位置
				char* begin = p;
				char* p2 = needle;
				p++;
				p2++;
				while (*p2 != '\0' && *p != '\0') {
					if (*p2 == *p) {
						p2++;
						p++;
					}
					else {
						break;
					}
				}
				// 如果 p2结束，表示成功匹配
				if (*p2 == '\0') {
					return (begin- haystack);
				}
				// 否则说明以 begin 开头的字符串虽然第一个字母匹配，但是后序字符不匹配
				// 从 begin 下一个继续检查
				else {
					p = begin + 1;
				}

			}
			else {
				p++;
			}
		}
		return -1;
	}
}
```

然后通过测试用例用了**1440 ms**，遇到首字母相同就要匹配，匹配失败又要从下一个开始，如果有很多个首字母都和`needle`相同，这个算法是不是很蠢。突然想到，大学《数据结构》书似乎有一种 KMP 算法，专门解决字符串子串的问题，赶快去找被垫在桌子角下面的《数据结构》，去翻一下。说好的简单题，一点都不简单。



## 解法二：KMP 算法

参考了网上的一些教程，发现这篇教程说的尤为的详细，有兴趣的小伙伴可以去看看：https://zhuanlan.zhihu.com/p/83334559

```c
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
// KMP 算法的实现，详细的思路可以参考 https://zhuanlan.zhihu.com/p/83334559

/**
* 构建一个 db[strlen(pattern)][256] 长度的二维数组
* db[j][c] = next 表示 db 从当前状态 j 遇到 字符 c 转化为 next 状态，
* next 可能是推进，也可能是后退，取决 c 是否可以与 pattern[j] 匹配
* 用 dp 来控制整个匹配的状态转移
*/
int** initDP(char* pattern) {
	int m = strlen(pattern);
	// ASCII 所有字符的个数，用来表示当前状态 j 遇到字符 c 如何进行状态转移
	int cMax = 256;
	int** dp = (int**)malloc(sizeof(int *) * m);
	int* firstChars = (int*)malloc(sizeof(int) * cMax);
	// 对 0 状态进行初始化
	for (int i = 0; i < cMax; i++) {
		*(firstChars + i) = 0;
	}
	// 只有 0 转态遇到 pattern 第一个字符时，才将状态转换为 1 状态
	int firstCharIndex = *(pattern + 0);
	*(firstChars + firstCharIndex) = 1;
	*(dp + 0) = firstChars;
	// 定义影子状态 x,当遇到非推进状态，需要根据影子状态来判断回退到哪一个状态
	int x = 0;
	for (int i = 1; i < m; i++) {
		// 初始化状态
		int* chars = (int*)malloc(sizeof(int) * cMax);
		for (int j = 0; j < cMax; j++) {
			*(chars + j) = *(*(dp + x) + j);
		}
		// 遇到 pattern[i] 才能转移到下个状态
		int index = *(pattern + i);
		*(chars + index) = i + 1;
		*(dp + i) = chars;
		// 重新计算影子状态
		x = *(*(dp + x) + index);
	}
	return dp;
}

int kmpSearch(char* text, char* pattern) {
	if (*pattern == '\0') {
		return 0;
	}
	else {
		int** dp = initDP(pattern);
		char* p = text;
		int m = strlen(pattern);
		// 初始状态为 0
		int j = 0;
		while (*p != '\0') {
			int index = *p;
			j = *(*(dp + j) + index);
			if (j == m) {
				return ((p - text) - m + 1);
			}
			p++;
		}
		return -1;
	}
}

int strStr(char* haystack, char* needle) {
	return kmpSearch(haystack, needle);
}
```

使用 KMP 算法后，通过测试用例的时间为**60ms**左右，只击败 23.3%的用户，我来看看究竟是什么方法竟然比 KMP 更牛逼。

## 解法三 修改后的暴力法

```c
int strStr(char* haystack, char* needle) {
	char* p1 = haystack;
	char* p2 = needle;
	// 开始位置 t
	char* t = p1;
	while (*p1 != '\0' && *p2 != '\0') {
		if (*p1 == *p2) { // 相等，各自自增
			p1++;
			p2++;
		}
		else { // 否则记录下次开始的位置 t,让p1 继续，且让 p2 重新开始
			t++;
			p1 = t;
			p2 = needle;
		}
	}
	if (*p2 == '\0') {
		return (t - haystack);
	}
	else {
		return -1;
	}
}
```

运行时间竟然是**4m**，比 KMP 还快，但是看了一眼算法的实现，还是会回头扫描，怎么能比 KMP 更高效呢。

我们使用下面的测试用例来跑一下：

```c
void effectiveCompare() {
	// 让 haystackSize = aaa...aaab
	// 让 needleSize = aaa...aaab
	// 这样使用暴力法会造成很多冗余的重复
	int haystackSize = 1000001;
	char* haystack = (char*)malloc(sizeof(char) * (haystackSize + 1));
	int i = 0;
	while (i < haystackSize - 1) {
		*(haystack + i) = 'a';
		i++;
	}
	*(haystack + i) = 'b';
	i++;
	*(haystack + i) = '\0';
	int needleSize = 2001;
	char* needle = (char*)malloc(sizeof(char) * (needleSize + 1));
	i = 0;
	while (i < needleSize - 1) {
		*(needle + i) = 'a';
		i++;
	}
	*(needle + i) = 'b';
	i++;
	*(needle + i) = '\0';
	printf("compare begin===========\n");
	long int b = getCurrentSeconds();
	int r1 = strStr(haystack, needle);
	long int e1 = getCurrentSeconds();
	int r2= kmpSearch(haystack, needle);
	long int e2 = getCurrentSeconds();
	printf("r1 is: %d, get r1 took: %d\n", r1,(e1-b));
	printf("r2 is: %d, get r2 took: %d\n", r2,(e2-e1));
}
```

然后我们发现暴力法用了**7s**，kmp 连 1s 都没用到，看了 leetcode 测试用例不够全面啊。