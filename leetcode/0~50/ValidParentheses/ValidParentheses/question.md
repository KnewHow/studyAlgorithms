# Question

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

这道题目其实是数据结构`栈`的一个应用，当我们遇见`(`、`[`或者是`{`时，我们把它们压入栈，遇到`)`、`]`或者是`}`我们比较栈顶元素是否可以与之构成一个完整的括号，如果是，将栈顶元素弹出，继续比较下一个，否则返回 `false`。

```c
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

typedef struct Element {
	char c; // 存储（、[ 或者 {
	struct Element* next;
} Element, *PElement;

// 压栈
PElement put(PElement head, char c) {
	if (head == NULL) {
		head = (PElement)malloc(sizeof(Element));
		head->c = c;
		head->next = NULL;
		return head;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = head;
		return e;
	}
}

// 弹栈
PElement pop(PElement head) {
	if (head != NULL) {
		return head->next;
	}
	else {
		return NULL;
	}
}

// 获取栈顶元素
PElement getPop(PElement head) {
	if (head != NULL) {
		return head;
	}
	else {
		return NULL;
	}
}

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
```

