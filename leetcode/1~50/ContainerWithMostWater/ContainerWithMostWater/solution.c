#include<stdlib.h>
#include<stdio.h>

int minValue(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

int maxArea(int* height, int heightSize) {
	int max = 0;
	for (int i = 0; i < heightSize; i++) {
		for (int j = i + 1; j < heightSize; j++) {
			int t = minValue(height[i], height[j]) * (j - i);
			if (t > max) {
				max = t;
			}
		}
	}
	return max;
}

int maxAreaWithTwoPointer(int* height, int heightSize) {
	int* head = height;
	int* tail = height + heightSize - 1;
	int max = minValue(*head, *tail) * (tail - head);
	while (head < tail) {
		int t = minValue(*head, *tail) * (tail - head);
		if (t > max) {
			max = t;
		}
		if (*head > * tail) {
			tail--;
		}
		else {
			head++;
		}
	}
	return max;
}

int main() {
	int arr[] = { 1,8,6,2,5,4,8,3,7 };
	int r = maxAreaWithTwoPointer(arr, sizeof(arr) / sizeof(int));
	printf("r is:%d", r);
	system("pause");
	return 0;
}