#include<stdlib.h>
#include<stdio.h>

void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}

/**
* ������������ȡ�����ַ��������ݴ�����ַ�����ȷ�����ֵ����Ǹ�λ��ʮλ���ǰ�λ
* @param num ���������֣���Χ�� 1-9 ֮��
* @param  one 10^k ���ַ���1-I, 10-X, 100-C
* @param five 5*10^k ���ַ��� 5-V, 50-L, 500-D
* @return ������ʾ���ֵ������ַ���
*/
char* getRoman(int num, char one, char five, char ten) {
	char* str = (char*)malloc(5 * sizeof(char));
	int size = 0;
	switch (num)
	{
	case 0:
		break;
	case 1:
		str[size++] = one;
		break;
	case 2:
		str[size++] = one;
		str[size++] = one;
		break;
	case 3:
		str[size++] = one;
		str[size++] = one;
		str[size++] = one;
		break;
	case 4:
		str[size++] = one;
		str[size++] = five;
		break;
	case 5:
		str[size++] = five;
		break;
	case 6:
		str[size++] = five;
		str[size++] = one;
		break;
	case 7:
		str[size++] = five;
		str[size++] = one;
		str[size++] = one;
		break;
	case 8:
		str[size++] = five;
		str[size++] = one;
		str[size++] = one;
		str[size++] = one;
		break;
	case 9:
		str[size++] = one;
		str[size++] = ten;
		break;

	default:
		break;
	}
	str[size++] = '\0';
	return str;
}

int getSize(char* str) {
	int size = 0;
	while (str[size] != '\0') {
		size++;
	}
	return size;
}

void concatStr(char* s1, char* s2) {
	int size = getSize(s1);
	char* tail = s1 + size;
	char* p = s2;
	while (*p != '\0') {
		*tail = *p;
		p++;
		tail++;
	}
	*tail = '\0';
}


char* intToRoman(int num) {
	int arr[10] = { 0 };
	// ��ȡnum ��λ����
	int n = num;
	int size = 0;
	while (n > 0) {
		arr[size++] = n % 10;
		n = n / 10;
	}
	char* romanStr = (char*)malloc(1024 * sizeof(char));
	*romanStr = '\0';
	int rSize = 0;
	char* r = NULL;
	// ���򣬴����λ����
	for (int i = size - 1; i >= 0; i--) {
		switch (i)
		{
		case 0: // ��λ
			r = getRoman(arr[i], 'I', 'V', 'X');
			concatStr(romanStr, r);
			break;
		case 1: // ʮλ
			r = getRoman(arr[i], 'X', 'L', 'C');
			concatStr(romanStr, r);
			break;
		case 2: // ��λ
			r = getRoman(arr[i], 'C', 'D', 'M');
			concatStr(romanStr, r);
			break;
		case 3: // ǧλ,���ڲ����� 3000���������λʹ�� \0 ����
			r = getRoman(arr[i], 'M', '\0', '\0');
			concatStr(romanStr, r);
			break;
		default:
			break;
		}
		// ���� r
		if (r != NULL) {
			free(r);
		}
	}
	return romanStr;
}

int main() {
	char * r = intToRoman(3999);
	printf("roman number is:%s", r);
	free(r);
	system("pause");
	return 0;
}