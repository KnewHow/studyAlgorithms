#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

/**
* ����ԭʼ�ַ�����ȡ���֣����е�һ���ַ���ʾ���ֵ� + ������ -
* ������Ŀ��Ҫ�󣬺����ַ����Ŀո񣬵�һ���ǿո���ַ����� '+' �� '-'����������Ϊ�Ϸ��ַ�
* ������Ҫ����Щ�ַ�ת��Ϊ����
*/
char* getNumber(char* str) {
	char* nums = (char*)malloc(sizeof(char) * 1024);
	char* p = str;
	int size = 0;
	while (*p != '\0') {
		if (*p == '+' || *p == '-') {
			if (size == 0) { // ���������ŵ�ʱ��size ������0��������Ժ���ģ�����ѭ��
				nums[size++] = *p; 
			}
			else {
				break;
			}
		}
		else if (*p == ' ') {
			if (size != 0) { // ������Ѿ��洢���ֺ������ո����ж�ѭ��
				break;
			}
		}
		else if (*p >= '0' && *p <= '9') {
			if (size == 0) { // ���������һ�����֣����� size ����Ϊ 0����ʾ�Ǹ�����
				nums[size++] = '+';
			}
			nums[size++] = *p;
		}
		else {// �����ַ�
			// �����������ַ�ʱ�����size ==0����ʾ�������ַ���ʼ��atoi Ӧ�÷��� 0
			if (size == 0) {
				free(nums);
				nums = NULL;
			}
			break;
		}
		p++;
	}
	if (size == 0) { // ���ַ���
		return NULL;
	} else if (nums == NULL) {// ��Ч���ַ���
		return NULL;
	} else {
		nums[size] = '\0'; // �ַ���������ʶ
		return nums;
	}
}

/**
* ��һ���ַ��������ַ���ת��Ϊ��������
*/
int myAtoi(char* str) {
	char* numbers = getNumber(str);
	if (numbers == NULL) {
		return 0;
	}
	else {
		long long num = 0;
		char* p = numbers;
		long long sign = 1;
		if (*p == '-') {
			sign = -1;
		}
		p++;
		while (*p != '\0') {
			int n = *p - 48; // ���ַ�����ת��Ϊ��������
			num = num * 10 + n;
			if (sign == 1 && num > INT_MAX) { // ��������ֱ�ӷ��� int ��ֵ
				return INT_MAX;
			}
			if (sign == -1 && (num * sign) < INT_MIN) {
				return INT_MIN;
			}
			p++;
		}
		return num * sign;
	}
}

int main() {
	char arr[] = "-5-";
	int r = myAtoi(arr);
	int r2 = atoi(arr);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}