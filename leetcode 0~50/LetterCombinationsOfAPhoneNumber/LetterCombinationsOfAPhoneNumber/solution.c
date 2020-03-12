#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>


// �����ܹ������ַ���������
int clcTotal(char* digits, char** map) {
	if (strlen(digits) == 0) {
		return 0;
	}
	else {
		char* p = digits;
		int total = 1;
		while (*p != '\0') {
			int pos = *p - 48; // ���ַ�����ת��Ϊ����
			total = total * strlen(*(map + pos));
			p++;
		}
		return total;
	}
	
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
	// ���ֽǱ굽�ַ�����ӳ��
	char* map[10] = {"", "","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
	// ���ֽǱ굽�ַ��� size ��ӳ��
	int mapSize[10] = { 0,0,3,3,3,3,3,4,3,4 };
	int total = clcTotal(digits, map);
	int size = strlen(digits);
	*returnSize = total;
	int counter = 0;
	char** r = (char**)malloc(total * sizeof(char*));
	while (counter < total) {
		char* str = (char*)malloc(sizeof(char) * (size + 1));
		// �� i ��ʾ������ digist �ĵ� i ���ַ�
		int i = 0;
		// ÿ��ѭ����sum * ��ǰ���ִ����ַ����ĳ��ȣ���������ѭ��
		int sum = 1;
		while (i < size) {
			// �ַ�����ת��Ϊ��Ӧ int
			int pos = *(digits + i) - 48;
			// ��������ִ�����ַ����м�λ
			int s = *(mapSize + pos);
			// �ôα���������ַ��Ǳ�
			int index = (counter / sum) % s;
			char c = *(*(map+pos) + index);
			*(str + i) = c;
			sum = sum * s;
			i++;
		}
		*(str + i) = '\0';
		*(r + counter) = str;
		counter++;
	}
	return r;
}

int main() {
	char arr[] = "9";
	int returnSize = 0;
	char** r = letterCombinations(arr, &returnSize);
	printf("[");
	for (int i = 0; i < returnSize; i++) {
		if (i == returnSize - 1) {
			printf("\"%s\"", *(r + i));
		}
		else {
			printf("\"%s\", ", *(r + i));
		}
	}
	printf("]\n");
	system("pause");
	return 0;
}