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
* ʹ�� KMP �㷨������ pattern ���ַ��� s �е�����λ��
* @param s ԭ�ַ��� s
* @param pattern ��Ҫƥ����ַ���
* @returnSize int ����ָ�룬���������Ĵ�С���ظ�������
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
			// ����ҵ��ˣ��ǿ�ʼ�ĽǱ꣬Ȼ�� j��Ϊ��ʼ״̬
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