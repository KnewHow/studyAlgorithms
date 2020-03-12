#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

int** initDP(char* pattern) {
	int size = strlen(pattern);
	int cMax = 256;
	int** dp = (int**)malloc(sizeof(int*) * size);
	int* first = (int*)malloc(sizeof(int) * cMax);
	for (int i = 0; i < cMax; i++) {
		*(first + i) = 0;
	}
	int index = *(pattern + 0);
	*(first + index) = 1;
	*(dp + 0) = first;
	int x = 0;
	for (int i = 1; i < size; i++) {
		int* arr = (int*)malloc(sizeof(int) * cMax);
		for (int j = 0; j < cMax; j++) {
			*(arr + j) = *(*(dp + x) + j);
		}
		int pos = *(pattern + i);
		*(arr +pos) = i + 1;
		*(dp + i) = arr;
		x = *(*(dp + x) + pos);
	}
	return dp;
}

void freeDP(int** dp, int size) {
	for (int i = 0; i < size; i++) {
		free(*(dp + i));
	}
	free(dp);
}

int kmpSearch(char* s, char* pattern) {
	int** dp = initDP(pattern);
	int j = 0;
	int n = strlen(s);
	int m = strlen(pattern);
	char* p = s;
	while (*p != '\0') {
		int index = *p;
		j = *(*(dp + j) + index);
		if (j == m) {
			freeDP(dp, m);
			return (p - s) - m + 1;
		}
		p++;
	}
	freeDP(dp, m);
	return -1;
}

void printArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d,", *(arr + i));
		}
	}
	printf(" ]\n");
}


/**
* 使用 KMP 算法来查找 pattern 在字符串 s 中的所有位置
* @param s 原字符串 s
* @param pattern 需要匹配的字符串
* @returnSize int 类型指针，将结果数组的大小返回给调用者
*/
int* kmpSearchAll(char* s, char* pattern, int *returnSize) {
	int n = strlen(s);
	int m = strlen(pattern);
	int* result = (int*)malloc(sizeof(int) * n);
	int size = 0;
	char* p = s;
	int** dp = initDP(pattern);
	int j = 0;
	while (*p != '\0') {
		int pos = *p;
		j = dp[j][pos];
		if (j == m) {
			// 如果找到了，记开始的角标，然后将 j置为初始状态
			*(result + size++) = (p - s) - m + 1;
			j = 0;
		}
		p++;
	}
	*returnSize = size;
	freeDP(dp, m);
	return result;
}

void testKmpSearchAll() {
	char* s = "aaaab";
	char* pattern = "a";
	int size = 0;
	int *r = kmpSearchAll(s, pattern,&size);
	printArray(r, size);
}