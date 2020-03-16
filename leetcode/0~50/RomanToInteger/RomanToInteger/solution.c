#include<stdio.h>
#include<stdlib.h>

// hashTable Ϊ�˶�ȡ���ݷ��㣬index Ϊ�������ֶ�Ӧ�� ASCII ֵ��
// value �Ƕ�Ӧ������ֵ
int hashTable[1024] = { 0 };

void put(char c, int value) {
	int index = c;
	hashTable[index] = value;
}

int get(char c) {
	int index = c;
	return hashTable[index];
}

// ��hashTable ��ʼ��
void initHashTable() {
	char cs[] = { 'I','V','X','L','C','D','M' };
	int  vs[] = {1,5,10,50,100,500,1000};
	for (int i = 0; i < sizeof(cs) / sizeof(char); i++) {
		put(cs[i], vs[i]);
	}
}

// c1 �����������Ƿ�� c2 ���������ִ�
// 1-�� 0-��
int isGreater(char c1, char c2) {
	if (get(c1) > get(c2)) {
		return 1;
	}
	else {
		return 0;
	}
}

int romanToInt(char* s) {
	initHashTable();
	char* head = s;
	char* next = head + 1;
	int sum = 0;
	while (*head != '\0' && *next != '\0') {
		// ��һ����ǰһ����,��ʾ��������
		if (isGreater(*next, *head)) {
			int v1 = get(*next);
			int v2 = get(*head);
			int v = v1 - v2;
			sum += v;
			head += 2;
			next += 2;
		}
		else { // ��������
			int v = get(*head);
			sum += v;
			head++;
			next++;
		}
	}
	// ��ֹ *next Ϊ�յ���©�����һ������
	if (*head != '\0') {
		int v = get(*head);
		sum += v;
	}
	return sum;
}

int main() {
	char arr[] = "MCMXCIV";
	int num = romanToInt(arr);
	printf("roman:%s to number is:%d\n", arr, num);
	system("pause");
	return 0;
}