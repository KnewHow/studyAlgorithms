#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/**
* 计算一个大数乘以一个简单数,例如12345 * 5，这里的 5 不是表示五，而是 5*10^n
* @param bigNum 较大数的字符串
* @param singleNum 简单数
* @param n 简单数的实际指数，即 singleNum * 10^n
* @return 返回一个新字符串，用来存储乘积的结构
*/
char* multiplySingle(char* bigNum, char singleNum, int n) {
	int totalSize = strlen(bigNum) + 1 + n + 1;
	char* res = (char*)malloc(sizeof(char) * totalSize);
	char* p = res;
	int size = strlen(bigNum);
	// 将末尾的 0 先补齐
	for (int i = 0; i < n; i++) {
		*p++ = '0';
	}
	// 每次乘积的进位
	int extra = 0;
	for (int i = size; i--; i >= 0) {
		char c = *(bigNum + i);
		int v1 = c - 48;
		int v2 = singleNum - 48;
		int r = v1 * v2 + extra;
		int left = r % 10;
		extra = r / 10;
		char leftC = left + 48;
		*p++ = leftC;

	}
	if (extra != 0) {
		char c = extra + 48;
		*p++ = c;
	}
	*p = '\0';
	return res;
}

/**
* 将每次的乘积进行累加
* @param res 存储所有乘积的字符串数组
* @param size 字符串数组大小
* @return 返回所有字符串数字相加的结果
*/
char* addResult(char** res, int size) {
	char* r = (char*)malloc(sizeof(char) * 300);
	// 标记第 i 个字符串是否已经结束 1-结束 0-没有结束
	int* tags = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(tags + i) = 0;
	}
	char* p = r;
	int j = 0;
	// 每次相加的和
	int sum = 0;
	// 进位
	int extra = 0;
	while (1) {
		int isAllEmpty = 1;
		sum = 0;
		for (int i = 0; i < size; i++) {
			if (*(tags + i) == 1) {
				continue;
			}
			else {
				char* s = *(res + i);
				if (*(s + j) == '\0') {
					*(tags + i) = 1;
					continue;
				}
				else {
					isAllEmpty = 0;
					char c = *(s + j);
					int v = c - 48;
					sum += v;
				}
			}
		}
		if (isAllEmpty == 1) {
			break;
		}
		else {
			sum += extra;
			char num = sum % 10 + 48;
			extra = sum / 10;
			*p++ = num;
			j++;
		}
	}
	if (extra != 0) {
		char c = extra + 48;
		*p++ = c;
	}
	*p = '\0';
	free(tags);
	return r;
}

void stringReverse(char* s) {
	int size = strlen(s);
	int mid = size / 2;
	for (int i = 0; i < mid; i++) {
		char temp = *(s + i);
		*(s + i) = *(s + size - i - 1);
		*(s + size - i - 1) = temp;
	}
}

void freeRes(char** res, int size) {
	for (int i = 0; i < size; i++) {
		char* s = *(res + i);
		if (s != NULL) {
			free(s);
		}
	}
	free(res);
}

char* multiply(char* num1, char* num2) {
	if (*num1 == '0' || *num2 == '0') {
		return "0";
	}
	else {
		int size = strlen(num2);
		char** res = (char**)malloc(sizeof(char*) * size);
		int n = 0;
		for (int i = size - 1; i >= 0; i--) {
			*(res + i) = multiplySingle(num1, *(num2 + i), n++);
		}
		char* r = addResult(res, size);
		freeRes(res, size);
		stringReverse(r);
		return r;
	}
}

int main() {
	char* num1 = "140";
	char* num2 = "721";
	char* r = multiply(num1, num2);
	printf("r is:%s\n", r);
	system("pause");
	return 0;
}