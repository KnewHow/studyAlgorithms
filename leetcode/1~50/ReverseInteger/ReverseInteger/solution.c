#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

int reverse(int x) {
	long long int nums[20] = { 0 };
	int length = 0;
	while (x != 0) {
		int r = x % 10;
		nums[length] = r;
		length++;
		x = x / 10;
	}
	long long int sum = 0;
	for (int i = 0; i < length; i++) {
		sum = nums[i] + sum * 10;
	}
	if (sum > INT_MAX || sum < INT_MIN) {
		return 0;
	}
	else {
		return sum;
	}
}

int main() {
	int num = -321;
	long int r = reverse(num);
	printf("reverse result=%d\n", r);
	system("pause");
	return 0;
}