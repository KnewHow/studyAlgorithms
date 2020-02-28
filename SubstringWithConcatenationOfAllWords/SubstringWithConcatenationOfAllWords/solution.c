#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "kmp.h"

/**
* �Ƚ����ַ����Ƿ���ȣ���ȷ��� 1�����򷵻� 0
* @param s1Begin �ַ��� s1 ��ʼλ��
* @param s2End �ַ��� s1 �Ľ���λ��
* @param s2 �ַ��� s2
*/
int compareStr(
	char* s1Begin,
	char* s1End,
	char* s2
) {
	int n1 = (s1End - s1Begin + 1);
	int n2 = strlen(s2);
	if (n1 == n2) {
		char* p1 = s1Begin;
		char* p2 = s2;
		while (p1 <= s1End) {
			if (*p1++ != *p2++) {
				return 0;
			}
		}
		return 1;
	}
	else {
		return 0;
	}
}

/**
* ���ݵ�һ��Ԫ��Ϊλ����ǰ��ɨ������Ԫ�ص�λ�ã��������ɨ�赽
* �ͷ�������Ԫ����С�ĽǱ�(��ʼ�ĽǱ�)�����򷵻� -1
* @param s ԭ�ַ��� s
* @param words ��Ҫ���ҵ��ַ������飬���е�һ���Ѿ�ȷ����λ��
* @param wordsSize words �����С
* @@param status words ÿ��Ԫ�����Ե�ǰ��һ��Ԫ������λ��Ϊ���ĵ�ɨ������
*			��һ��Ԫ�ص�λ���Ѿ�ȷ��������Ԫ�ص�λ��ռλȷ����ʹ�� -1 ��ʶ
* @param step ���� words ����Ԫ�ض��ȳ����������� step ��ʾ
* @return ����Ե�һ��Ԫ��Ϊ�����ҵ����� word,������Щ word �ʼ�ĽǱ꣬���򷵻� -1
*/
int findOthers(
	char* s,
	char** words,
	int wordsSize,
	int* status,
	int step
) {
	// s �����һ��Ԫ��
	char* sEnd = (s + strlen(s) - 1);
	// ��ǰ��һ��Ԫ�س��ֵ�λ��
	char* p = s + *(status + 0);
	// �� p Ϊ���ĵ���������-1 ��ʾ����ɨ�裬1 ��ʾ����ɨ�裬0 ��ʾɨ����ֹ
	// ���ǲ�������ǰɨ��
	int direction = -1;
	// ��ǰ�Ѿ�������ɵĸ���
	int finished = 1;
	// �� p ��Ϊ���ģ���ǰɨ��Ĵ���
	int previousTimes = 0;
	// �� p ��Ϊ���ģ����ɨ��Ĵ���
	int nextTimes = 0;
	while (finished <= wordsSize && direction != 0) {
		if (direction == -1) { // ��ǰ����
			if (p - s >= (step * ++previousTimes)) { // ˵�� p ��ǰ�滹�г��� step ���ַ�
				char* begin = p - (step * previousTimes);
				char* end = p - 1 - step * (previousTimes - 1);
				int previousFinish = finished;
				for (int i = 1; i < wordsSize; i++) {
					if (*(status + i) == -1) { // ����û����������
						int r = compareStr(begin, end, *(words + i));
						if (r == 1) { // �ҵ���
							*(status + i) = begin - s;
							finished++;
							break; // �ж�ѭ��
						}
					}
					
				}
				// ����ҵ��˼����ң��������ұ���
				if (finished == previousFinish) {
					direction = 1;
				}
			}
			else {
				// p ������Ѿ�û�п��� step * previousTimes ���ַ����ˣ��ı䷽��
				direction = 1;
			}
		}
		else { // ��������
			// ����ұ߻��и��� step �ַ�����+1 ��ʾ p ����,����ɨ����ֹ
			int left = sEnd - p;
			if (sEnd - p >= (++nextTimes + 1) * step) {
				char* begin = p + (1 + (nextTimes - 1)) * step;
				char* end = p + ((1 + (nextTimes)) * step) - 1;
				int previousFinish = finished;
				for (int i = 1; i < wordsSize; i++) {
					if (*(status + i) == -1) {
						int r = compareStr(begin, end, *(words + i));
						if (r == 1) { // �ҵ���
							*(status + i) = begin - s;
							finished++;
						}
					}
				}
				// ����ҵ��˼����ң���������
				if (finished == previousFinish) {
					direction = 0;
				}
			}
			else {
				direction = 0;
			}
		}
	}
	int begin = *(status + 0);
	for (int i = 1; i < wordsSize; i++) {
		// û������ȫ������ʧ�ܽ�� -1
		if (*(status + i) == -1) {
			return -1;
		}
		else {
			if (*(status + i) < begin) {
				begin = *(status + i);
			}
		}
	}
	return begin;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
	int* r = (int*)malloc(sizeof(int) * strlen(s));
	int size = 0;
	if (wordsSize != 0) {
		int firstPositionArraySize = 0;
		// ����ÿ�� word ���ǵȳ��ģ������� step ��ʾÿ��Ԫ�صĳ���
		int step = strlen(*(words + 0));
		int* firstPositionArray = kmpSearchAll(s, *(words + 0), &firstPositionArraySize);
		// �������һ��Ԫ�س��ֵ�����λ�ý���ɨ��
		for (int i = 0; i < firstPositionArraySize; i++) {
			printf("first index:%d\n", *(firstPositionArray + i));
			/* ����һ��״̬���飬�� words ����һ����
			* ��ʾ words ÿ��Ԫ���Ե�һ��Ԫ��Ϊ������ɢ�ĽǱ� 
			*/
			int* status = (int*)malloc(sizeof(int) * wordsSize);
			// ��Ԫ�ص�λ���Ѿ��ҵ�
			*(status + 0) = *(firstPositionArray + i);
			for (int j = 1; j < wordsSize; j++) {
				// ����λ��ʹ�� -1 ��ʶδ�ҵ�
				*(status + j) = -1;
			}
			int begin = findOthers(s, words, wordsSize, status, step);
			if (begin != -1) {
				*(r + size++) = begin;
			}
			free(status);
		}
	}
	*returnSize = size;
	return r;
}


int main() {
	char* s = "barfoofoobarthefoobarman";
	char *words[] = { "bar","foo","the" };
	char wordsSize = 3;
	int returnSize = 0;
	int* r = findSubstring(s, words, wordsSize, &returnSize);
	printArray(r, returnSize);
	// testKmpSearchAll();
	system("pause");
	return 0;
}