#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int counterRec = 0;

/**
* 纯递归法
*/
int isMatch(char* s, char* p) {
	if (*s == '\0') {
		// 如果 s 为空， 如果 p 为空，或者剩下的 p 都是 * 匹配成功
		// 否则失败
		while (*p != '\0') {
			if (*p != '*') {
				return 0;
			}
			p++;
		}
		return 1;
	}
	else {
		if (*p == '*') {
			return isMatch(s, p + 1) || isMatch(s + 1, p);
		}
		else {
			int firstMatch = (*s == *p) || (*p == '?');
			return firstMatch && isMatch(s + 1, p + 1);
		}
	}
}

/**
* 匹配
* @param s 原字符 s
* @param p 模式字符串 p
* @param n s 的 size
* @param m p 的 size
* @param sIndex 当前比较到 s 中的那个角标
*/
int match(
	char* s,
	char* p,
	int n,
	int m,
	int sIndex,
	int pIndex,
	int** res) {
	counterRec++;
	// 如果已经计算过，直接返回
	if (*(*(res + sIndex) + pIndex) != -1) {
		return *(*(res + sIndex) + pIndex);
	}
	else {
		int r = 0;
		// s 已经结束，如果 p 结束或者 p 剩下的都是 *，则匹配成功
		if (sIndex == n) {
			if (pIndex == m) { // p 也结束
				r = 1;
			}
			else {
				r = 1;
				while (*(p + pIndex) != '\0') {
					if (*(p + pIndex) != '*') {
						r = 0;
						break;
					}
					pIndex++;
				}
			}
		}
		else {
			if (*(p + pIndex) == '*') {
				r = match(s, p, n, m, sIndex, pIndex + 1, res)
					|| match(s, p, n, m, sIndex + 1, pIndex, res);
			}
			else {
				int firstMathch = *(p + pIndex) == *(s + sIndex) ||
					*(p + pIndex) == '?';
				r = firstMathch && match(s, p, n, m, sIndex + 1, pIndex + 1, res);
			}
		}
		*(*(res + sIndex) + pIndex) = r;
		return r;
	}


}

void freeRes(int** res, int size) {
	for (int i = 0; i < size; i++) {
		int* arr = *(res + i);
		if (arr != NULL) {
			free(arr);
		}
	}
	free(res);
}

void printRes(int** res, int size, int colSize) {
	printf("[\n");
	for (int i = 0; i < size; i++) {
		int* arr = *(res + i);
		printf("\t");
		for (int j = 0; j < colSize; j++) {
			printf("%d ", *(arr + j));
		}
		printf("\n");
	}
	printf("]\n");
}

/**
* 记忆递归法
*/
int isMatch2(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int rows = n + 1;
	int cols = m + 1;
	int** res = (int**)malloc(sizeof(int*) * rows);
	for (int i = 0; i < rows; i++) {
		int* arr = (int*)malloc(sizeof(int) * cols);
		for (int j = 0; j < cols; j++) {
			*(arr + j) = -1;
		}
		*(res + i) = arr;
	}
	int r = match(s, p, n, m, 0, 0, res);
	freeRes(res, rows);
	return r;
}

/**
* 纯粹的动态规范解法
*/
int isMatch3(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int** res = (int**)malloc(sizeof(int*) * (m + 1));
	for (int i = 0; i < m + 1; i++) {
		int* arr = (int*)malloc(sizeof(int) * (n + 1));
		for (int j = 0; j < n + 1; j++) {
			*(arr + j) = 0;
		}
		*(res + i) = arr;
	}
	*(*(res + 0) + 0) = 1;
	for (int i = 1; i < m + 1; i++) {
		if (*(p + i - 1) == '*') {
			int sSize = 1;
			/* 找出之前成功匹配的一个点，如果之前都没有成功匹配，则 sSize = n+1，
			*  此时 res[i][n] = 0, 表示之前的匹配失败，则当前行 res[i][*] 全为 0
			*  若之前有匹配成功的 res[i-1][sSize-1] 项，
			*  则由于是 * 的关系，当前的 res[i][sSize-1] 可以理解为 * 和空字符匹配成功，后面的都匹配成功
			*/
			while (*(*(res + i - 1) + sSize - 1) != 1 && sSize < n + 1) {
				sSize++;
			}
			*(*(res + i) + sSize - 1) = *(*(res + i - 1) + sSize - 1);
			while (sSize < n + 1) {
				*(*(res + i) + sSize) = 1;
				sSize++;
			}
		}
		else if (*(p + i - 1) == '?') { // 如果为 ？，则之前的匹配，现在的也匹配
			for (int sSize = 1; sSize < n + 1; sSize++) {
				*(*(res + i) + sSize) = *(*(res + i - 1) + sSize - 1);
			}
		}
		else { // 如果不为 * 或者 ?，此时需要比较当前的 p[i-1] 和 s[sSize-1]的值，以及之前的比较结果
			for (int sSize = 1; sSize < n + 1; sSize++) {
				*(*(res + i) + sSize) = *(p + i - 1) == *(s + sSize - 1) 
					&& *(*(res + i - 1) + sSize - 1);
			}
		}
	}
	int r = *(*(res + m) + n);
	freeRes(res, m + 1);
	return r;
}

void testIsMatch2RecursiveCallTimes(int* s, int* p) {
	counterRec = 0;
	isMatch2(s, p);
	int n = strlen(s);
	int m = strlen(p);
	printf("isMatch recursive call times: %d, m x n is:%d\n", counterRec, n*m);
}

/**
* 回溯法
*/
int isMatch4(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int i = 0;
	int j = 0;
	int starIndex = -1; // 记录 p 中 * 角标
	int sTempIndex = -1; // 当 * 出现时， s 的对应角标
	while (i < n) {
		if (j < m && *(p + j) == '?' || *(p + j) == *(s + i)) {
			i++;
			j++;
		}
		else if (j < m && *(p + j) == '*') {
			starIndex = j;
			sTempIndex = i;
			j++;
		}
		else if (starIndex == -1) { // 在不匹配的情况下，有没有 * 可以回溯，直接返回 false
			return 0;
		}
		else { 
			j = starIndex + 1;
			i = sTempIndex + 1;
			sTempIndex = i;
		}
	}
	// 如果 s 结束时，如果 j 结束或者 j 后面都为 *,则匹配成功,否则匹配失败
	for (int k = j; k < m; k++) {
		if (*(p + k) != '*') {
			return 0;
		}
	}
	return 1;
}

int main() {
	char* s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	char* p = "a*******b";
	// testIsMatch2RecursiveCallTimes(s, p);
	 int r = isMatch4(s, p);
	 printf("r is %d\n", r);
	system("pause");
	return 0;
}