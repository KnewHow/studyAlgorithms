	# Question

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![](D:\project\studyAlgorithms\LetterCombinationsOfAPhoneNumber\LetterCombinationsOfAPhoneNumber\Telephone.svg.webp)

Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

首先我们建立一套2~9的字符串映射，当输入为字符串时，我们可以把他转换成数字的数组，我们假设每个数字对应的字符串有`ai`个，`i`表示下标，则总共的结果有`a1 * a2 * ... ai ... *an`个。我们只需要遍历所有的字符串，然后进行组合即可。

```c
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>


// 计算总共生成字符串的数量
int clcTotal(char* digits, char** map) {
	if (strlen(digits) == 0) {
		return 0;
	}
	else {
		char* p = digits;
		int total = 1;
		while (*p != '\0') {
			int pos = *p - 48; // 将字符数字转换为整数
			total = total * strlen(*(map + pos));
			p++;
		}
		return total;
	}
	
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
	// 数字角标到字符串的映射
	char* map[10] = {"", "","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
	// 数字角标到字符串 size 的映射
	int mapSize[10] = { 0,0,3,3,3,3,3,4,3,4 };
	int total = clcTotal(digits, map);
	int size = strlen(digits);
	*returnSize = total;
	int counter = 0;
	char** r = (char**)malloc(total * sizeof(char*));
	while (counter < total) {
		char* str = (char*)malloc(sizeof(char) * (size + 1));
		// 用 i 表示遍历到 digist 的第 i 个字符
		int i = 0;
		// 每次循环后，sum * 当前数字代表字符串的长度，用来控制循环
		int sum = 1;
		while (i < size) {
			// 字符数字转换为对应 int
			int pos = *(digits + i) - 48;
			// 计算该数字代表的字符串有几位
			int s = *(mapSize + pos);
			// 该次遍历所需的字符角标
			int index = (counter / sum) % s;
			char c = *(*(map+pos) + index);
			*(str + i) = c;
			sum = sum * s;
			i++;
		}
		*(str + i) = '\0';
		*(r + counter) = str;
		counter++;
	}
	return r;
}

int main() {
	char arr[] = "9";
	int returnSize = 0;
	char** r = letterCombinations(arr, &returnSize);
	printf("[");
	for (int i = 0; i < returnSize; i++) {
		if (i == returnSize - 1) {
			printf("\"%s\"", *(r + i));
		}
		else {
			printf("\"%s\", ", *(r + i));
		}
	}
	printf("]\n");
	system("pause");
	return 0;
}
```

