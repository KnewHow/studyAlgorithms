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
	// ����Ѿ��������ֱ�ӷ���
	if (*(*(res + sIndex) + pIndex) != -1) {
		return *(*(res + sIndex) + pIndex);
	}
	else {
		int r = 0;
		// s �Ѿ���������� p �������� p ʣ�µĶ��� *����ƥ��ɹ�
		if (sIndex == n) {
			if (pIndex == m) { // p Ҳ����
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