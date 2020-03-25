#include<stdlib.h>
#include<stdio.h>


int removeDuplicates(int* nums, int numsSize) {
	if (numsSize == 0) {
		return 0;
	}
	else {
		int previous = *(nums + 0);
		int size = 1;
		for (int i = 1; i < numsSize; i++) {
			if (*(nums + i) != previous) { // ÐÂÔªËØ
				*(nums + size) = *(nums + i);
				previous = *(nums + i);
				size++;
			}
		}
		return size;
	}
}

void printArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d, ", *(arr + i));
		}
	}
	printf(" ]\n");
}
int main() {
	int arr[] = { 0,0,1,1,1,2,2,3,3,4 };
	int size = sizeof(arr) / sizeof(int);
	int newSize = removeDuplicates(arr, size);
	printArray(arr, newSize);
	system("pause");
	return 0;
}