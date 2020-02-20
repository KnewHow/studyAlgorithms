#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include "stack.h"

int isValid(char* s) {
	char* p = s;
	PElement head = NULL;
	while (*p != '\0') {
		if (*p == '(' || *p == '[' || *p == '{') {
			// 压栈
			head = put(head, *p);
			p++;
		}
		else {
			// 比较栈顶元素是否和 *p 配对
			PElement e = getPop(head);
			if (head == NULL) { // 栈内无元素，不匹配
				return 0;
			}
			else {
				// 成功配对，弹栈，继续比较下一个
				if ((e->c == '(' && *p == ')')
					|| (e->c == '[' && *p == ']')
					|| (e->c == '{' && *p == '}')) {
					head = pop(head);
					p++;
				}
				else {
					return 0;
				}
			}
		}
	}
	// 最后当栈里没有元素，说明全部匹配，返回1，否则返回0
	PElement e = pop(head);
	if (head == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	char* str = "[";
	int r = isValid(str);
	printf("r is:%d", r);
	system("pause");
	return 0;
}