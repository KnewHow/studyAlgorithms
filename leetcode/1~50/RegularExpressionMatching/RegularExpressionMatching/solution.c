#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

// �����洢ƥ���������飬i` ��ʾԭ�ַ���`s`�еĽǱ꣬`j`��ʾģʽ�ַ���`p`�ĽǱ꣬
// `arr[i][j]` ��ʾ `s[i]` �� `p[j]` �Ƿ�ƥ�䣬
// ��������һ�εݹ�󱣴���ֵ���ڶ��εݹ����������Ϳ���ֱ�ӷ��أ�����Ҫ�������µݹ���
int arr[1024][1024] = { 0 };

int isEmpty(char* s) {
	if (*s == '\0') {
		return 1;
	}
	else {
		return 0;
	}
}

int size(char* s) {
	int size = 0;
	char* p = s;
	while (*p != '\0') {
		size++;
		p++;
	}
	return size;
}

int isMatch(char* s, char* p) {
	// ��� p Ϊ�գ��ж� s �Ƿ�ͬʱΪ��
	if (isEmpty(p)) {
		return isEmpty(s);
	}
	else {
		int firstMatch = !isEmpty(s) && (*s == *p || *p == '.');
		// ��ģʽ�ַ������ȴ���2����p[1] == '*',���ǿ��������·�����
		// 1 ֱ�Ӻ��� p[0],p[1],����ζ�� * ƥ�� 0 ���ַ�
		// 2 ������ * ƥ��һ���ַ���ȥ��ԭ�ַ���һ���ַ���Ȼ��ʹ�� p ����ƥ��
		if (size(p) >= 2 && *(p + 1) == '*') {
			return isMatch(s, p + 2) || (firstMatch && isMatch(s + 1, p));
		}
		else { // ���û�� * ƥ�䣬 ��һ��ƥ�� && �����ƥ��
			return firstMatch && isMatch(s + 1, p + 1);
		}
	}
}

// ��ʼ��ȫ�����飬�� -1 ������Ƿ�����
void initArray(int x, int y) {
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			arr[i][j] = -1;
		}
	}
}


/**
* ƥ���ַ�����ʹ�����鱣����,�Ż��ݹ���ظ�����
* @param s ԭʼ�ַ���
* @param p ģʽ�ַ���
* @param i ��ǰ�Ƚϵ� s �ַ�����ʼ�Ǳ�
* @param j ��ǰģʽ�ַ��� p ����ʼ�Ǳ�
* @param sSize �ַ��� s �� size,���뷽����Ϊ�߽��ж�����
* @param pSize �ַ��� p �� size,���뷽����Ϊ�߽���ж�����
* @return �˴��Ƿ�ƥ�� 1-ƥ�� 0-��ƥ��
*/
int match(
	char* s, 
	char* p, 
	int i, 
	int j, 
	int sSize, 
	int pSize
) {
	// ֮ǰ�Ѿ��������ֱ�ӷ��أ�����ʡȥ�ݹ����Ĵ�������Ҳ������㷨�������㷨�Ż��ĵط�
	if (arr[i][j] != -1) {
		return arr[i][j];
	}
	else { // ֮ǰû�м����������
		int r = 0;
		if (j == pSize) { // ��� p �Ѿ��������� s ��û�н���,�������� 1,���򷵻� 0
			if (i == sSize) {
				r = 1;
			}
			else {
				r = 0;
			}
		}
		else {
			int firstMatch = (i != sSize) && (s[i] == p[j] || p[j] == '.');
			// j �����ٻ���һ��Ԫ���� j + 1 �� *
			if (j + 1 < pSize && p[j + 1] == '*') {
				// ���Խ������ĳ�����Ϊ�������
				// 1. * û��ƥ�䣬����ֱ�����������Ƚ� s �� j + 2
				// 2. ���� * ƥ��ɹ��������Ƚ� s ����һ���Ƿ�ƥ�� *
				r = match(s, p, i, j + 2, sSize, pSize)
					|| (firstMatch && match(s, p, i + 1, j, sSize, pSize));
			}
			else {
				// ������� * �ţ���һ��ƥ�� && �����ƥ��
				r = firstMatch && match(s, p, i + 1, j + 1, sSize, pSize);
			}
		}
		// ����˴ν�������ں���ʹ��
		arr[i][j] = r;
		return r;
	}
}

int isMatchWithArray(char* s, char* p) {
	int sSize = size(s);
	int pSize = size(p);
	initArray(sSize, pSize);
	return match(s, p, 0, 0, sSize, pSize);
}


int main() {
	char s[] = "aa";
	char p[] = "a*";
	int r = isMatchWithArray(s, p);
	printf("is match r is:%d\n", r);
	system("pause");
	return 0;
}