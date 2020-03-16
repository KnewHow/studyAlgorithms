#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<math.h>

// ���ڴ洢���ս���Ķ�ά����
char **result = NULL;
// ����ĳ���
int size = 0;

/**
* ���Ѿ���ȡ�Ľ��ת��Ϊ��Ӧ���ַ���
* @param arr �Ѿ�����õ����飬��ÿ�� ( �����ж��ٸ� )
* @param n ��С����
*/
char* toString(int* arr, int n) {
	int total = 2 * n + 1;
	char* str = (char*)malloc(sizeof(char) * total);
	char* p = str;
	for (int i = 0; i < n; i++) {
		*p++ = '(';
		int times = *(arr + i);
		for (int j = 0; j < times; j++) {
			*p++ = ')';
		}
	}
	*p = '\0';
	return str;
}

void printArr(int * arr, int size) {
	printf("printArr strart=====\n");
	for (int i = 0; i < size; i++) {
		printf("%d, ", *(arr + i));
	}
	printf("\nprintArr end=====\n");
}

/**
* @param nth ��ǰ��nth��(����
* @param �ܹ��� n �� (
* @param preResult ��ǰ�Ľ������
* @param used ��ǰ�Ѿ�ʹ�õ� )
* @param left ��ǰʣ��� )
*/
void generate(int nth, int n, int* preResult, int used, int left) {
	// ����ֻ�м��㵽 n-1 ( �����ɣ���Ϊ�� n ������ʣ�¶��پ��Ƕ���
	if (nth < n) {
		// �� i �� ( ������������ i - used �� arr
		for (int i = 0; i <= nth - used; i++) {
			// ������������������
			int* newResult = (int*)malloc(sizeof(int) * nth);
			int j = 0;
			// �ϲ�ǰ��Ľ��
			for (int j = 0; j < nth - 1; j++) {
				*(newResult + j) = *(preResult + j);
			}
			// �ϲ���ǰ�Ľ��
			*(newResult + nth - 1) = i;
			// ������ = ֮ǰ���� + ��ǰ����
			// ʣ���� = ֮ǰʣ�� - ��ǰ����
			generate(nth + 1, n, newResult, used + i, left - i);
			/*if (newResult != NULL) {
				free(newResult);
			}*/
		}
	}
	else {
		// ����n����˵���Ѿ��������һ������ʣ�µ���Ϊ���һ������� ) ����
		int* newResult = (int*)malloc(sizeof(int) * nth);
		// �ϲ�ǰ��Ľ��
		for (int j = 0; j < nth - 1; j++) {
			*(newResult + j) = *(preResult + j);
		}
		// �ϲ���ǰ�Ľ��
		*(newResult + nth - 1) = left;
		// �����Ѿ����� n ��(����ÿ��( �����ж��ٸ� ),���ǿ��Ը�����Щ���ݹ���һ���������ַ���
		*(result + size) = toString(newResult, n);
		size++;
		/*if (newResult != NULL) {
			free(newResult);
		}*/
	}
}


char** generateParenthesis(int n, int* returnSize) {
	result = (char**)malloc(sizeof(10240 * sizeof(char*)));
	generate(1, n, NULL, 0, n);
	*returnSize = size;
	return result;
}

int main() {
	int returnSize = 0;
	char** r = generateParenthesis(5, &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%s\n", *(r + i));
	}
	system("pause");
	return 0;
}