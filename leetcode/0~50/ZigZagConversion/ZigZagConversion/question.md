# Question

将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zigzag-conversion
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

建立一个长度为 `numRows`的 hashTable 来存储每行的元素，后来的插入链表的尾节点。现在的问题是如何根据角标来确定当前字符在哪一行，我们做如下分析：

给定一个行数 m,那么元素将会以`2m-2`来重复构造，当`m=3`时，看第一个示例，元素会每4次重复一下，`LEET`、`OCDE`……；当 `m=4`时，看第二个示例，元素将会每6次构造重复一次，那么我们如何判断角标`i`在第几行呢？

首先我们需要计算`r = i % 2m-2`,我们知道我们 hashMap 的最大角标是 `m-1`，如果 `r <= m-1`, 那么 `row = r`,否则 `row = m-1 - (r-(m-1)) = 2(m-1) -  r`。

代码如下：

```c
#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

typedef struct Element {
	char c;
	struct Element* next;
} Element, * PElement;

typedef struct Head {
	PElement head;
	PElement tail;
} Head, *Phead;

Phead* init(int size) {
	Phead* hashTable = (Phead*)malloc(sizeof(Phead) * size);
	if (hashTable == NULL) {
		printf("init hashTable error: malloc failure");
		return NULL;
	}
	else {
		for (Phead* p = hashTable; p < hashTable + size; p++) {
			*p = NULL;
		}
		return hashTable;
	}
}

void put(Phead* hashTable, int index, char c) {
	Phead head = hashTable[index];
	if (head == NULL) {
		head = (Phead)malloc(sizeof(Head));
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = NULL;
		head->head = e;
		head->tail = e;
		hashTable[index] = head;
	}else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->c = c;
		e->next = NULL;
		head->tail->next = e;
		head->tail = e;
	}
}

char* toString(Phead* hashTable, int size, int row) {
	char* str = (char*)malloc(sizeof(char) * (size + 1));
	char* p = str;
	for (int i = 0; i < row; i++) {
		Phead head = hashTable[i];
		if (head != NULL) {
			PElement temp = head->head;
			while (temp != NULL) {
				*p = temp->c;
				p++;
				temp = temp->next;
			}
		}
	}
	*p = '\0';
	return str;
}

char* convert(char* s, int numRows) {
	Phead* hashTable = init(numRows);
	int counter = 0;
	int l = 2 * numRows - 2;
	if (l == 0) {
		return s;
	}
	else {
		while (s[counter] != '\0') {
			int r = counter % l;
			int index = 0;
			if (r > (numRows - 1)) {
				index = 2 * (numRows - 1) - r;
			}
			else {
				index = r;
			}
			put(hashTable, index, s[counter]);
			counter++;
		}
		return toString(hashTable, counter, numRows);
	}
}
```

