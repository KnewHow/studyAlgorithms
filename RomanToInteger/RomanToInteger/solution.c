#include<stdio.h>
#include<stdlib.h>

// hashTable 为了读取数据方便，index 为罗马数字对应的 ASCII 值，
// value 是对应的整数值
int hashTable[1024] = { 0 };

void put(char c, int value) {
	int index = c;
	hashTable[index] = value;
}

int get(char c) {
	int index = c;
	return hashTable[index];
}

// 对hashTable 初始化
void initHashTable() {
	char cs[] = { 'I','V','X','L','C','D','M' };
	int  vs[] = {1,5,10,50,100,500,1000};
	for (int i = 0; i < sizeof(cs) / sizeof(char); i++) {
		put(cs[i], vs[i]);
	}
}

// c1 的罗马数字是否比 c2 的罗马数字大
// 1-是 0-否
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
		// 后一个比前一个大,表示减法运算
		if (isGreater(*next, *head)) {
			int v1 = get(*next);
			int v2 = get(*head);
			int v = v1 - v2;
			sum += v;
			head += 2;
			next += 2;
		}
		else { // 正常叠加
			int v = get(*head);
			sum += v;
			head++;
			next++;
		}
	}
	// 防止 *next 为空导致漏掉最后一个数字
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