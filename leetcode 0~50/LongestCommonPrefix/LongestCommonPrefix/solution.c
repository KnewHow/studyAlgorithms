#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

/**
*  比较当前角标下字符串数组元素是否全部相等
* @param strs 原字符串数组
* @param index 当前的下标
* @param strsSize 字符串数组大小
* @return 0-不相等 1-相等
*/
int isSame(char** strs, int index, int strsSize) {
	char first = strs[0][index];
	for (int i = 0; i < strsSize; i++) {
		// 当字符串已经结束时，返回 false
		if (strs[i][index] == '\0' || strs[i][index] != first) {
			return 0;
		}
	}
	return 1;
}

char* longestCommonPrefix(char** strs, int strsSize) {
	// 当为空数组时，直接返回空字符串
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