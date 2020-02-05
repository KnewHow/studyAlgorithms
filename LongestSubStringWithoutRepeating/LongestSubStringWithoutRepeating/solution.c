#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

// index Ϊ�ַ��� ASCII ��ֵ��value Ϊ�ַ��� index
int hashTable[128] = { 0 };

// �� hashTable ����Ԫ�س�ʼ��Ϊ -1
void init() {
	for (int i = 0; i < sizeof(hashTable) / sizeof(int); i++) {
		hashTable[i] = -1;
	}
}

void push(char c, int pos) {
	int index = c;
	hashTable[index] = pos;
}

int isRepeat(char c) {
	int index = c;
	if (hashTable[index] == -1) {
		return 0;
	}
	else {
		return 1;
	}
}

// ��ȡԪ�ص�λ��
int getPos(char c) {
	int index = c;
	return hashTable[index];
}

// ��ֵС�� pos Ԫ����Ϊ -1
void reset(char *begin,char * end) {
	char* p = begin;
	while (p <= end) {
		int index = *p;
		hashTable[index] = -1;
		p++;
	}
}

int lengthOfLongestSubstring(char* s) {
	int maxSize = 0;
	int currentSize = 0;
	char* p = s;
	// ��ǰ�ַ�������λ��
	char* begin = s;
	init();
	while (*p != '\0') {
		// �ظ���
		if (isRepeat(*p)) {
			if (currentSize > maxSize) {
				maxSize = currentSize;
			}
			int pos = getPos(*p);
			reset(begin, s + pos);
			currentSize = (p-s)-pos;
			begin = (s + pos) + 1;
			push(*p, p-s);
		}
		else { // δ�ظ�
			currentSize++;
			push(*p, p-s);
		}
		p++;
	}
	if (currentSize > maxSize) {
		maxSize = currentSize;
	}
	return maxSize;
}


int main() {
	char arr[] = "abcabcbb";
	int size = lengthOfLongestSubstring(arr);
	printf("mas substring size=%d", size);
	system("pause");
	return 0;
}