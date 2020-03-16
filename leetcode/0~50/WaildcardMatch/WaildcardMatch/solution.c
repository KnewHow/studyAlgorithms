#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int counterRec = 0;

/**
* ���ݹ鷨
*/
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
	int** res) {
	counterRec++;
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
* ����ݹ鷨
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
* ����Ķ�̬�淶�ⷨ
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
			/* �ҳ�֮ǰ�ɹ�ƥ���һ���㣬���֮ǰ��û�гɹ�ƥ�䣬�� sSize = n+1��
			*  ��ʱ res[i][n] = 0, ��ʾ֮ǰ��ƥ��ʧ�ܣ���ǰ�� res[i][*] ȫΪ 0
			*  ��֮ǰ��ƥ��ɹ��� res[i-1][sSize-1] �
			*  �������� * �Ĺ�ϵ����ǰ�� res[i][sSize-1] �������Ϊ * �Ϳ��ַ�ƥ��ɹ�������Ķ�ƥ��ɹ�
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
		else if (*(p + i - 1) == '?') { // ���Ϊ ������֮ǰ��ƥ�䣬���ڵ�Ҳƥ��
			for (int sSize = 1; sSize < n + 1; sSize++) {
				*(*(res + i) + sSize) = *(*(res + i - 1) + sSize - 1);
			}
		}
		else { // �����Ϊ * ���� ?����ʱ��Ҫ�Ƚϵ�ǰ�� p[i-1] �� s[sSize-1]��ֵ���Լ�֮ǰ�ıȽϽ��
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
* ���ݷ�
*/
int isMatch4(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int i = 0;
	int j = 0;
	int starIndex = -1; // ��¼ p �� * �Ǳ�
	int sTempIndex = -1; // �� * ����ʱ�� s �Ķ�Ӧ�Ǳ�
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
		else if (starIndex == -1) { // �ڲ�ƥ�������£���û�� * ���Ի��ݣ�ֱ�ӷ��� false
			return 0;
		}
		else { 
			j = starIndex + 1;
			i = sTempIndex + 1;
			sTempIndex = i;
		}
	}
	// ��� s ����ʱ����� j �������� j ���涼Ϊ *,��ƥ��ɹ�,����ƥ��ʧ��
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