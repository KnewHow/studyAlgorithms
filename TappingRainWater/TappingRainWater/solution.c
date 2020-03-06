#include<stdio.h>
#include<stdlib.h>

int clcWater(int* height, int begin, int end) {
	if (end - begin > 1) { // ֻ�м����� 1 �ż���
		// �ҳ����߶ȵ���Сֵ��Ϊ��
		int v1 = *(height + begin);
		int v2 = *(height + end);
		int v = min(v1, v2);
		int total = v * (end - begin + 1);
		// ��ȥʵ�Ĳ��֣�����߶ȳ����ˣ�����С�߶�Ϊ׼
		for (int i = begin; i <= end; i++) {
			int h = *(height + i);
			if (h > v) {
				h = v;
			}
			total -= h;
		}
		return total;
	}
	else {
		return 0;
	}
}

int trap(int* height, int heightSize) {
	if (heightSize <= 1) {
		return 0;
	}
	else {
		int sum = 0;
		int i = 0;
		// �ӵ�һ����Ϊ0�Ŀ�ʼ
		while (i < heightSize) {
			if (*(height + i) == 0) {
				i++;
			}
			else {
				break;
			}
		}
		int beginIndex = i;
		int begin = *(height + i);
		i++;
		for (; i < heightSize; i++) {
			if (*(height + i) >= begin) {
				sum += clcWater(height, beginIndex, i);
				begin = *(height + i);
				beginIndex = i;
			}
		}
		// ���ѭ������� begin Ӧ�������������ֵ�ˣ�������Ҫ����������һ��
		// �ҳ��� begin ̫�߶�©���Ĳ���
		int max = begin;
		int maxIndex = beginIndex;
		i = heightSize - 1;
		while (i > maxIndex) {
			if (*(height + i) == 0) {
				i--;
			}
			else {
				break;
			}
		}
		begin = *(height + i);
		beginIndex = i;
		i--;
		for (; i >= maxIndex; i--) {
			if (*(height + i) >= begin) {
				sum += clcWater(height, i, beginIndex);
				begin = *(height + i);
				beginIndex = i;
			}
		}
		return sum;
	}
}

int main() {
	int height[] = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	int size = sizeof(height) / sizeof(int);
	int sum = trap(height, size);
	printf("sum is:%d\n", sum);
	system("pause");
	return 0;
}