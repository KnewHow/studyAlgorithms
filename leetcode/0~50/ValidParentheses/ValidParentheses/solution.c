#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include "stack.h"

int isValid(char* s) {
	char* p = s;
	PElement head = NULL;
	while (*p != '\0') {
		if (*p == '(' || *p == '[' || *p == '{') {
			// ѹջ
			head = put(head, *p);
			p++;
		}
		else {
			// �Ƚ�ջ��Ԫ���Ƿ�� *p ���
			PElement e = getPop(head);
			if (head == NULL) { // ջ����Ԫ�أ���ƥ��
				return 0;
			}
			else {
				// �ɹ���ԣ���ջ�������Ƚ���һ��
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
	// ���ջ��û��Ԫ�أ�˵��ȫ��ƥ�䣬����1�����򷵻�0
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