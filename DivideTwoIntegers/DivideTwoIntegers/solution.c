#include<stdlib.h>
#include<stdio.h>

int divR(int divident, int divisor) {
	if (divident > divisor) {
		return 0;
	}
	else {
		// ����������ʼ��Ϊ-1�������������
		int counter = -1;
		// ����� tb ʹ�� long long ���ͣ���Ȼ���ܻ�������ݵ����
		long long int tb = divisor;
		while ((tb + tb) > divident) {
			// ÿ���� counter �� divisor ��������� divident = -12 dividor=-2
			// ����ֻ��Ҫ���� 4 �ξͿɣ���ԭ��ÿ�η�һ�ο��˺ܶ�
			// �� divisor * 2^n ���ٶ�������
			counter = counter + counter;
			tb = tb + tb;
		}
		return counter + divR(divident - tb, divisor);
	}
}

int divide(int dividend, int divisor) {
	// -1 �� +1 �����⴦��
	if (divisor == 1) {
		return dividend;
	}
	if (divisor == -1) {
		if (dividend == INT_MIN) {
			return INT_MAX;
		}
		else {
			return -dividend;
		}
	}
	// ���ű�־λ��ͬ��Ϊ1�����Ϊ-1
	int tag = 1;
	if ((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0)) {
		tag = 1;
	}
	else {
		tag = -1;
	}

	// ȫ�����ɸ������㣬��Ϊ��������������
	if (dividend > 0) {
		dividend = -dividend;
	}
	if (divisor > 0) {
		divisor = -divisor;
	}

	int quotient = divR(dividend, divisor);
	if (tag == -1) {
		return quotient;
	}
	else {
		if (quotient <= INT_MIN) {
			return INT_MAX;
		}
		else {
			return -quotient;
		}
	}
}

int main() {
	int dividend = 2147483647;
	int divisor = 3;
	int quotient = divide(dividend, divisor);
	printf("quotient is %d\n", quotient);
	system("pause");
	return 0;
}