#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include"hashTable.h"

// 定义回文序列的返回值
typedef struct Palindrome {
	int begin;
	int end;
	int length;
} Palindrome;

/**
 * 判断起始位置的字符串是否为回文序列，是，返回回文字符串的起始位置和长度。
 * 否则返回 length = 0 的 Palindrome
 * @param begin 起始角标
 * @param end 结束角标
 * @param s 原始字符串
*/
Palindrome judgePalindromeWithIndex(
	int begin,
	int end,
	char* s
) {
	int b = begin;
	int e = end;
	Palindrome p = { 0,0,0 };
	while (b <= e) {
		// 不是回文序列
		if (s[b] != s[e]) {
			return p;
		}
		else {
			b++;
			e--;
		}
	}
	// 是回文序列
	p.begin = begin;
	p.end = end;
	p.length = end - begin + 1;
	return p;
}

/**
 * 判断当前位置元素是否有回文子串，如果不存在，返回的 Palindrome 的 length 0
 * @param hashTable 存放当前元素的 hashTable
 * @param c 当前已存在的字符
 * @param currentIndex 当前已存在元素的位置
 * @param s 原始字符串
 * @param currentLength 当前已经确定的回文串的长度
 */
Palindrome judgePalindrome(
	PElement* hashTable,
	char c,
	int currentIndex,
	char* s,
	int currentLength
) {
	Palindrome p = { 0,0,0 };
	PHead head = get(hashTable, c);
	// 该字符不重复，一般不会出现这样的情况，如果出现了，返回长度为 0 的 Palindrome
	if (head == NULL) {
		return p;
	}
	else {
		PElement temp = head->head;
		int begin = 0;
		int end = 0;
		int length = 0;
		while (temp != NULL) {
			// 当需要测试的回文序列比当前的长度大的时候，才进行测试
			if (currentIndex - temp->index + 1 > currentLength) {
				Palindrome r = judgePalindromeWithIndex(temp->index, currentIndex, s);
				// 由于是从距离当前元素最远的重复元素开始，如果找到了，则就已经是最大了，终止循环
				if (r.length > length) {
					begin = r.begin;
					end = r.end;
					length = r.length;
					break;
				}
			}
			temp = temp->next;
		}
		p.begin = begin;
		p.end = end;
		p.length = length;
		return p;
	}
}

char* longestPalindrome(char* s) {
	PElement* hashTable = init();
	char* p = s;
	int size = 0;
	int begin = 0; // 当前最长回文序列起始位置
	int end = 0; // 当前最长回文序列结束位置
	int length = 0; // 当前回文序列的长度
	while (*p != '\0') {
		if (isExists(hashTable, *p)) {
			// 如果 *p 已经存在，当前位置和已存在位置之间是否存在回文序列
			Palindrome r = judgePalindrome(hashTable, *p, (p - s), s, length);
			if (r.length > length) {
				begin = r.begin;
				end = r.end;
length = r.length;
			}
		}
		put(hashTable, *p, (p - s));
		p++;
		size++;
	}
	// 没有找到长度大于1的回文串
	if (length == 0) {
		// 若为空字符串，返回空字符串
		if (size == 0) {
			char* pa = (char*)malloc(1 * sizeof(char));
			pa[0] = '\0';
			return pa;
		}
		else { // 否则返回字符串的首元素(任意元素均可)
			char* pa = (char*)malloc(2 * sizeof(char));
			pa[0] = s[0];
			pa[1] = '\0';
			return pa;
		}
	}
	else {
		char* pa = (char*)malloc((end - begin + 2) * sizeof(char));
		for (int i = begin; i <= end; i++) {
			pa[i - begin] = s[i];
		}
		pa[end - begin + 1] = '\0';
		return pa;
	}
}

int getSize(char* s) {
	int size = 0;
	char* p = s;
	while (*p != '\0') {
		size++;
		p++;
	}
	return size;
}

char* preDealString(char* s) {
	int size = getSize(s);
	if (size == 0) {
		return "^$";
	}
	else {
		char* newS = (char*)malloc((size * 2 + 4) * sizeof(char));
		char* p1 = s;
		char* p2 = newS;
		*p2 = '^';
		p2++;
		while (*p1 != '\0') {
			*p2 = '#';
			p2++;
			*p2 = *p1;
			p2++;
			p1++;
		}
		*p2 = '#';
		p2++;
		*p2 = '$';
		p2++;
		*p2 = '\0';
		return newS;
	}
}

char* subString(char* s, int begin, int end) {
	char* r = (char*)malloc(end - begin + 1);
	char* p = r;
	for (int i = begin; i < end; i++) {
		*p = s[i];
		p++;
	}
	*p = '\0';
	return r;
}

// 使用 Manacher 算法
char* longestPalindromeWithManacher(char* s) {
	char * newS = preDealString(s);
	int newSize = getSize(newS);
	int c = 0; // 当前回文串的对称中心
	int r = 0; // 以 c 位中心， 当前最长回文串的右半径
	// 与新字符对于的一个整型数组，存储以对应字符为中心的回文串的半径
	int* p = (int*)malloc(sizeof(int) * newSize);
	for (int i = 1; i < newSize - 1; i++) { // 忽略首字母 ^ 和为字母 $
		 // 以 c 为对称点，i 和 iMirror 关于 c 成中心对称的回文串
		int iMirror = 2 * c - i;
		// 当 i 还以 c 为中心， r 为右半径的回文对称字符串内
		if (r > i) {
			// 这里以 i 为对称中心，如果 i + 右半径(p[i]) 还在以 c 为中心, r为右半径的回文串内
			// 则 p[i] = p[i_Mirror],
			// 否则说明字符结束或者需要再次对 i 为中心的回文串进行判定,但是可以知道 p[i] 最起码大于等于 r - i
			p[i] = r - i < p[iMirror] ? r - i : p[iMirror];
		}
		else {
			p[i] = 0; // 否则 p[i] = 0;
		}
		// 对 i 进行中心扩展
		while (newS[i + 1 + p[i]] == newS[i - 1 - p[i]]) {
			p[i] ++;
		}
		// 对 i 进行的中心扩展的右半径如果已经超过 r,则将新的对称中心置为 i, 对称半径置为 i + p[i]
		if (i + p[i] > r) {
			c = i;
			r = i + p[i];
		}
	}

	// 找出最长的 index 和 半径
	int longestIndex = 0; 
	int longest = 0;
	for (int i = 1; i < newSize - 1; i++) {
		if (p[i] > longest) {
			longestIndex = i;
			longest = p[i];
		}
	}

	int begin = (longestIndex - longest) / 2; // 由于扩展过，这里需要 / 2
	int end = begin + longest; // 由于扩展过，这里只加一半即可
	return subString(s, begin, end);

}





int main() {
	char arr[] = "cbcbccde";
	/*for (int i = 0; i < 1000; i++) {
		arr[i] = 'z';
	}
	arr[1000] = '\0';*/
	char * r = longestPalindromeWithManacher(arr);
	printf("longest palindrome sub string is: %s\n", r);
	system("pause");
	return 0;
}