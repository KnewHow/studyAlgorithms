#include<stdio.h>
#include<stdlib.h>

double doPow(double x, long long int n) {
	if (n == 0) {
		return 1;
	}
	else if (n == -1) {
		return x;
	}
	else {
		long long int counter = -1;
		double r = x;
		while ((counter + counter) >= n) {
			r *= r;
			counter += counter;
		}
		return r * doPow(x, n - counter);
	}
}

double myPow(double x, int n) {
	if (n == 0) {
		return 1;
	}
	else if(n < 0){
		return 1 / doPow(x, n);
	}
	else { // 统一化为负数计算，避免溢出
		return doPow(x, -n);
	}
}

int main() {
	double x = 1;
	int n = -2147483647 -1;
	double r = myPow(x, n);
	printf("r is :%f\n", r);
	printf("INT_MIN is: %d\n", INT_MIN);
	system("pause");
	return 0;
}