#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
// KMP �㷨��ʵ�֣���ϸ��˼·���Բο� https://zhuanlan.zhihu.com/p/83334559

/**
* ����һ�� db[strlen(pattern)][256] ���ȵĶ�ά����
* db[j][c] = next ��ʾ db �ӵ�ǰ״̬ j ���� �ַ� c ת��Ϊ next ״̬��
* next �������ƽ���Ҳ�����Ǻ��ˣ�ȡ�� c �Ƿ������ pattern[j] ƥ��
* �� dp ����������ƥ���״̬ת��
*/
int** initDP(char* pattern) {
	int m = strlen(pattern);
	// ASCII �����ַ��ĸ�����������ʾ��ǰ״̬ j �����ַ� c ��ν���״̬ת��
	int cMax = 256;
	int** dp = (int**)malloc(sizeof(int *) * m);
	int* firstChars = (int*)malloc(sizeof(int) * cMax);
	// �� 0 ״̬���г�ʼ��
	for (int i = 0; i < cMax; i++) {
		*(firstChars + i) = 0;
	}
	// ֻ�� 0 ת̬���� pattern ��һ���ַ�ʱ���Ž�״̬ת��Ϊ 1 ״̬
	int firstCharIndex = *(pattern + 0);
	*(firstChars + firstCharIndex) = 1;
	*(dp + 0) = firstChars;
	// ����Ӱ��״̬ x,���������ƽ�״̬����Ҫ����Ӱ��״̬���жϻ��˵���һ��״̬
	int x = 0;
	for (int i = 1; i < m; i++) {
		// ��ʼ��״̬
		int* chars = (int*)malloc(sizeof(int) * cMax);
		for (int j = 0; j < cMax; j++) {
			*(chars + j) = *(*(dp + x) + j);
		}
		// ���� pattern[i] ����ת�Ƶ��¸�״̬
		int index = *(pattern + i);
		*(chars + index) = i + 1;
		*(dp + i) = chars;
		// ���¼���Ӱ��״̬
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
		// ��ʼ״̬Ϊ 0
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
