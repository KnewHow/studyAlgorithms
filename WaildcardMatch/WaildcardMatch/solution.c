#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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
	int **res) {
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

int main() {
	char* s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	char* p = "a*******b";
	int r = isMatch2(s, p);
	printf("r is %d\n", r);
	system("pause");
	return 0;
}