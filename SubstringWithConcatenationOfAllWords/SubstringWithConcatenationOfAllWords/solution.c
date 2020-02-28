#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "kmp.h"

/**
* 比较两字符串是否相等，相等返回 1，否则返回 0
* @param s1Begin 字符串 s1 开始位置
* @param s2End 字符串 s1 的结束位置
* @param s2 字符串 s2
*/
int compareStr(
	char* s1Begin,
	char* s1End,
	char* s2
) {
	int n1 = (s1End - s1Begin + 1);
	int n2 = strlen(s2);
	if (n1 == n2) {
		char* p1 = s1Begin;
		char* p2 = s2;
		while (p1 <= s1End) {
			if (*p1++ != *p2++) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

/**
* 根据第一个元素为位置来前后扫描其他元素的位置，如果可以扫描到
* 就返回所有元素最小的角标(开始的角标)，否则返回 -1
* @param s 原字符串 s
* @param words 需要查找的字符串数组，其中第一个已经确定了位置
* @param wordsSize words 数组大小
* @@param status words 每个元素在以当前第一个元素所在位置为中心的扫描结果，
*			第一个元素的位置已经确定，其他元素的位置占位确定，使用 -1 标识
* @param step 由于 words 所有元素都等长，这里用于 step 表示
* @return 如果以第一个元素为中心找到其余 word,返回这些 word 最开始的角标，否则返回 -1
*/
int findOthers(
	char* s,
	char** words,
	int wordsSize,
	int* status,
	int step
) {
	// s 的最后一个元素
	char* sEnd = (s + strlen(s) - 1);
	// 当前第一个元素出现的位置
	char* p = s + *(status + 0);
	// 以 p 为中心的搜索方向，-1 表示向左扫描，1 表示向右扫描，0 表示扫描终止
	// 我们不妨先往前扫描
	int direction = -1;
	// 当前已经搜索完成的个数
	int finished = 1;
	// 以 p 点为中心，向前扫描的次数
	int previousTimes = 0;
	// 以 p 点为中心，向后扫描的次数
	int nextTimes = 0;
	while (finished <= wordsSize && direction != 0) {
		if (direction == -1) { // 向前搜索
			if (p - s >= (step * ++previousTimes)) { // 说明 p 的前面还有超过 step 个字符
				char* begin = p - (step * previousTimes);
				char* end = p - 1 - step * (previousTimes - 1);
				int previousFinish = finished;
				for (int i = 1; i < wordsSize; i++) {
					if (*(status + i) == -1) { // 搜索没有搜索过的
						int r = compareStr(begin, end, *(words + i));
						if (r == 1) { // 找到了
							*(status + i) = begin - s;
							finished++;
							break; // 中断循环
						}
					}
					
				}
				// 如果找到了继续找，否则像右边找
				if (finished == previousFinish) {
					direction = 1;
				}
			}
			else {
				// p 左边面已经没有可以 step * previousTimes 的字符串了，改变方向
				direction = 1;
			}
		}
		else { // 向右搜索
			// 如果右边还有更多 step 字符串，+1 表示 p 本身,否则扫描终止
			int left = sEnd - p;
			if (sEnd - p >= (++nextTimes + 1) * step) {
				char* begin = p + (1 + (nextTimes - 1)) * step;
				char* end = p + ((1 + (nextTimes)) * step) - 1;
				int previousFinish = finished;
				for (int i = 1; i < wordsSize; i++) {
					if (*(status + i) == -1) {
						int r = compareStr(begin, end, *(words + i));
						if (r == 1) { // 找到了
							*(status + i) = begin - s;
							finished++;
						}
					}
				}
				// 如果找到了继续找，否则不找了
				if (finished == previousFinish) {
					direction = 0;
				}
			}
			else {
				direction = 0;
			}
		}
	}
	int begin = *(status + 0);
	for (int i = 1; i < wordsSize; i++) {
		// 没有找完全，返回失败结果 -1
		if (*(status + i) == -1) {
			return -1;
		}
		else {
			if (*(status + i) < begin) {
				begin = *(status + i);
			}
		}
	}
	return begin;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	int* r = (int*)malloc(sizeof(int) * strlen(s));
	int size = 0;
	if (wordsSize != 0) {
		int firstPositionArraySize = 0;
		// 由于每个 word 都是等长的，可以用 step 表示每个元素的长度
		int step = strlen(*(words + 0));
		int* firstPositionArray = kmpSearchAll(s, *(words + 0), &firstPositionArraySize);
		// 对数组第一个元素出现的所有位置进行扫描
		for (int i = 0; i < firstPositionArraySize; i++) {
			printf("first index:%d\n", *(firstPositionArray + i));
			/* 构建一个状态数组，和 words 长度一样，
			* 表示 words 每个元素以第一个元素为中心扩散的角标 
			*/
			int* status = (int*)malloc(sizeof(int) * wordsSize);
			// 首元素的位置已经找到
			*(status + 0) = *(firstPositionArray + i);
			for (int j = 1; j < wordsSize; j++) {
				// 其它位置使用 -1 标识未找到
				*(status + j) = -1;
			}
			int begin = findOthers(s, words, wordsSize, status, step);
			if (begin != -1) {
				*(r + size++) = begin;
			}
			free(status);
		}
	}
	*returnSize = size;
	return r;
}


int main() {
	char* s = "barfoofoobarthefoobarman";
	char *words[] = { "bar","foo","the" };
	char wordsSize = 3;
	int returnSize = 0;
	int* r = findSubstring(s, words, wordsSize, &returnSize);
	printArray(r, returnSize);
	// testKmpSearchAll();
	system("pause");
	return 0;
}