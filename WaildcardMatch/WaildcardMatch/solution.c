#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int isMatch(char* s, char* p) {
	if (*s == '\0') {
		// ��� s Ϊ�գ� ��� p Ϊ�գ�����ʣ�µ� p ���� * ƥ��ɹ�
		// ����ʧ��
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
* ƥ��
* @param s ԭ�ַ� s
* @param p ģʽ�ַ��� p
* @param n s �� size
* @param m p �� size
* @param sIndex ��ǰ�Ƚϵ� s �е��Ǹ��Ǳ�
*/
int match(
	char* s,
	char* p,
	int n,
	int m,
	int sIndex, 
	int pIndex, 
	int **res) {
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
	for (int i = 0; i < n; i++) {
		int* arr = (int*)malloc(sizeof(int) * cols);
		for (int j = 0; j < m; j++) {
			*(arr + j) = -1;
		}
		*(res + i) = arr;
	}
}

int main() {
	char* s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
	char* p = "a*******b";
	int r = isMatch(s, p);
	printf("r is %d\n", r);
	system("pause");
	return 0;
}