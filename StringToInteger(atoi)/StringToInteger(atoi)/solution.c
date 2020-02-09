#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

/**
* 根据原始字符串提取数字，其中第一个字符表示数字的 + 或者是 -
* 根据题目的要求，忽略字符串的空格，第一个非空格的字符若是 '+' 、 '-'或是数字则为合法字符
* 我们需要将这些字符转换为整数
*/
char* getNumber(char* str) {
	char* nums = (char*)malloc(sizeof(char) * 1024);
	char* p = str;
	int size = 0;
	while (*p != '\0') {
		if (*p == '+' || *p == '-') {
			if (size == 0) { // 遇到正负号的时候，size 必须是0，否则忽略后面的，跳出循环
				nums[size++] = *p; 
			}
			else {
				break;
			}
		}
		else if (*p == ' ') {
			if (size != 0) { // 如果在已经存储数字后遇到空格，则中断循环
				break;
			}
		}
		else if (*p >= '0' && *p <= '9') {
			if (size == 0) { // 如果遇到第一个数字，但是 size 还是为 0，表示是个正数
				nums[size++] = '+';
			}
			nums[size++] = *p;
		}
		else {// 其他字符
			// 当遇到其它字符时，如果size ==0，表示以其它字符开始，atoi 应该返回 0
			if (size == 0) {
				free(nums);
				nums = NULL;
			}
			break;
		}
		p++;
	}
	if (size == 0) { // 空字符串
		return NULL;
	} else if (nums == NULL) {// 无效的字符串
		return NULL;
	} else {
		nums[size] = '\0'; // 字符串结束标识
		return nums;
	}
}

/**
* 将一个字符串整数字符串转换为数字整数
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
			int n = *p - 48; // 将字符数字转换为整型数字
			num = num * 10 + n;
			if (sign == 1 && num > INT_MAX) { // 如果溢出，直接返回 int 极值
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