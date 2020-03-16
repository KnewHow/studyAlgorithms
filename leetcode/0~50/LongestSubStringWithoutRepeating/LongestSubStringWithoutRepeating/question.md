# Question

Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Answer

这道题的关键在于如何判断该字符在已有字符串中是否已存在，我们可以使用 HashTable 来做到O(1)时间的运算。每个字符都有一个 ASCII 值，我们声明一个数组，对于已存在的字符，将该字符对应的下标在元素进行标记。如果发现重复，判断当前子串是否大于已经查找到最大子串。是，改变 maxSize 的 值，并将 HashTable 的值清空，重新查找。

```c
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

// index 为字符的 ASCII 码值，value 为字符的 index
int hashTable[128] = { 0 };

// 将 hashTable 所有元素初始化为 -1
void init() {
	for (int i = 0; i < sizeof(hashTable) / sizeof(int); i++) {
		hashTable[i] = -1;
	}
}

void push(char c, int pos) {
	int index = c;
	hashTable[index] = pos;
}

int isRepeat(char c) {
	int index = c;
	if (hashTable[index] == -1) {
		return 0;
	}
	else {
		return 1;
	}
}

// 获取元素的位置
int getPos(char c) {
	int index = c;
	return hashTable[index];
}

// 将值小于 pos 元素置为 -1
void reset(char *begin,char * end) {
	char* p = begin;
	while (p <= end) {
		int index = *p;
		hashTable[index] = -1;
		p++;
	}
}

int lengthOfLongestSubstring(char* s) {
	int maxSize = 0;
	int currentSize = 0;
	char* p = s;
	// 当前字符串的首位置
	char* begin = s;
	init();
	while (*p != '\0') {
		// 重复了
		if (isRepeat(*p)) {
			if (currentSize > maxSize) {
				maxSize = currentSize;
			}
			int pos = getPos(*p);
			reset(begin, s + pos);
			currentSize = (p-s)-pos;
			begin = (s + pos) + 1;
			push(*p, p-s);
		}
		else { // 未重复
			currentSize++;
			push(*p, p-s);
		}
		p++;
	}
	if (currentSize > maxSize) {
		maxSize = currentSize;
	}
	return maxSize;
}


int main() {
	char arr[] = "abcabcbb";
	int size = lengthOfLongestSubstring(arr);
	printf("mas substring size=%d", size);
	system("pause");
	return 0;
}
```

