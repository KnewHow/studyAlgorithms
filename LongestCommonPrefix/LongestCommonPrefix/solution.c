#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

/**
*  �Ƚϵ�ǰ�Ǳ����ַ�������Ԫ���Ƿ�ȫ�����
* @param strs ԭ�ַ�������
* @param index ��ǰ���±�
* @param strsSize �ַ��������С
* @return 0-����� 1-���
*/
int isSame(char** strs, int index, int strsSize) {
	char first = strs[0][index];
	for (int i = 0; i < strsSize; i++) {
		// ���ַ����Ѿ�����ʱ������ false
		if (strs[i][index] == '\0' || strs[i][index] != first) {
			return 0;
		}
	}
	return 1;
}

char* longestCommonPrefix(char** strs, int strsSize) {
	// ��Ϊ������ʱ��ֱ�ӷ��ؿ��ַ���
	if (strsSize < 1) {
		return "";
	}
	else {
		int begin = 0;
		while (isSame(strs, begin, strsSize)) {
			begin++;
		}
		if (begin == 0) {
			return "";
		}
		else {
			char* r = (char*)malloc((begin + 1) * sizeof(char));
			int i = 0;
			char* p = r;
			while (i < begin) {
				*p = strs[0][i];
				p++;
				i++;
			}
			*p = '\0';
			return r;
		}
	}
}

int main() {
	char* arr[] = {""};
	char* r = longestCommonPrefix(arr, 1);
	printf("longest common prefix is:%s", r);
	system("pause");
	return 0;
}