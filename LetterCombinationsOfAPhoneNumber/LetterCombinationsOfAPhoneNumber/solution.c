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