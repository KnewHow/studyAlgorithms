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
