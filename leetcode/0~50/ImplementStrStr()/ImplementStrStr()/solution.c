#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "kmp.h"

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

int strStrWithKmp(char* haystack, char* needle) {
	return kmpSearch(haystack, needle);
}


// 获取当前毫秒值
long int getCurrentSeconds() {
	time_t t;
	time(&t);
	return t;
}

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

int main() {
	effectiveCompare();
	system("pause");
	return 0;
}