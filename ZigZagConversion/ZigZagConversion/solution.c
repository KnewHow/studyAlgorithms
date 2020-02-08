#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include "hashTable.h"

char* convert(char* s, int numRows) {
	Phead* hashTable = init(numRows);
	int counter = 0;
	int l = 2 * numRows - 2;
	if (l == 0) {
		return s;
	}
	else {
		while (s[counter] != '\0') {
			int r = counter % l;
			int index = 0;
			if (r > (numRows - 1)) {
				index = 2 * (numRows - 1) - r;
			}
			else {
				index = r;
			}
			put(hashTable, index, s[counter]);
			counter++;
		}
		return toString(hashTable, counter, numRows);
	}
}

int main() {
	char arr[] = "A";
	int numRows = 1;
	char* r = convert(arr, numRows);
	printf("r is:%s\n", r);
	system("pause");
	return 0;
}