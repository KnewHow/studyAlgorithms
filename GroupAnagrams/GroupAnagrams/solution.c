#include<stdio.h>
#include<stdlib.h>
#include "hashtable.h"

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
	PHashTable hashTable = initHashTable();
	for (int i = 0; i < strsSize; i++) {
		push(hashTable, *(strs + i), i);
	}
	return toGroup(hashTable, strs, returnSize, returnColumnSizes);
}


char** createStrs(char* strsMode[], int size) {
	char** strs = (char**)malloc(sizeof(char*) * size);
	for (int i = 0; i < size; i++) {
		*(strs + i) = *(strsMode + i);
	}
	return strs;
}

void printStrs(char*** strs, int row, int* cols) {
	printf("[\n");
	for (int i = 0; i < row; i++) {
		int col = *(cols + i);
		char** strArray = *(strs + i);
		printf("\t[");
		for (int j = 0; j < col; j++) {
			if (j == col - 1) {
				printf("%s ", *(strArray + j));
			}
			else {
				printf("%s, ", *(strArray + j));
			}
		}
		printf("]\n");
	}
	printf("]\n");
}

int main() {
	char* strsMode[] = {
		"cab","tin","pew","duh","may","ill","buy","bar","max","doc"
	};
	int size = 10;
	int row = 0;
	int* cols = NULL;
	char** strs = createStrs(strsMode, size);
	char*** r = groupAnagrams(strs, size, &row, &cols);
	printStrs(r, row, cols);
	// testGetStrArray();
	system("pause");
	return 0;
}