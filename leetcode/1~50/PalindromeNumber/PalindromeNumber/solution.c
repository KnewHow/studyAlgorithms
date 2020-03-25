#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

int isPalindrome(int x) {
	if (x < 0) { // 负数不可能为回文数
		return 0;
	}
	else {
		int a[1024] = { 0 };
		int size = 0;
		long long int num = x;
		while (num != 0) {
			a[size++] = num % 10;
			num = num / 10;
		}
		long long int newNum = 0;
		for (int i = 0; i < size; i++) {
			newNum = newNum * 10 + a[i];
			// 如果超出 INT_MAX 不可能为回文数
			if (newNum > INT_MAX) {
				return 0;
			}
		}
		return x == newNum;
	}
}

int main() {
	int x = 2147483647;
	int r = isPalindrome(x);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}