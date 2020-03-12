#include<stdlib.h>
#include<stdio.h>

int removeElement(int* nums, int numsSize, int val) {
	int size = 0;
	for (int i = 0; i < numsSize; i++) {
		if (*(nums + i) != val) {
			*(nums + size) = *(nums + i);
			size++;
		}
	}
	return size;
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
	int arr[] = { 0,1,2,2,3,0,4,2 };
	int size = sizeof(arr) / sizeof(int);
	int val = 2;
	int newSize = removeElement(arr, size, val);
	printArray(arr, newSize);
	system("pause");
	return 0;
}