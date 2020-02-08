#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include"hashTable.h"

// ����������еķ���ֵ
typedef struct Palindrome {
	int begin;
	int end;
	int length;
} Palindrome;

/**
 * �ж���ʼλ�õ��ַ����Ƿ�Ϊ�������У��ǣ����ػ����ַ�������ʼλ�úͳ��ȡ�
 * ���򷵻� length = 0 �� Palindrome
 * @param begin ��ʼ�Ǳ�
 * @param end �����Ǳ�
 * @param s ԭʼ�ַ���
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
		// ���ǻ�������
		if (s[b] != s[e]) {
			return p;
		}
		else {
			b++;
			e--;
		}
	}
	// �ǻ�������
	p.begin = begin;
	p.end = end;
	p.length = end - begin + 1;
	return p;
}

/**
 * �жϵ�ǰλ��Ԫ���Ƿ��л����Ӵ�����������ڣ����ص� Palindrome �� length 0
 * @param hashTable ��ŵ�ǰԪ�ص� hashTable
 * @param c ��ǰ�Ѵ��ڵ��ַ�
 * @param currentIndex ��ǰ�Ѵ���Ԫ�ص�λ��
 * @param s ԭʼ�ַ���
 * @param currentLength ��ǰ�Ѿ�ȷ���Ļ��Ĵ��ĳ���
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
	// ���ַ����ظ���һ�㲻������������������������ˣ����س���Ϊ 0 �� Palindrome
	if (head == NULL) {
		return p;
	}
	else {
		PElement temp = head->head;
		int begin = 0;
		int end = 0;
		int length = 0;
		while (temp != NULL) {
			// ����Ҫ���ԵĻ������бȵ�ǰ�ĳ��ȴ��ʱ�򣬲Ž��в���
			if (currentIndex - temp->index + 1 > currentLength) {
				Palindrome r = judgePalindromeWithIndex(temp->index, currentIndex, s);
				// �����ǴӾ��뵱ǰԪ����Զ���ظ�Ԫ�ؿ�ʼ������ҵ��ˣ�����Ѿ�������ˣ���ֹѭ��
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
	int begin = 0; // ��ǰ�����������ʼλ��
	int end = 0; // ��ǰ��������н���λ��
	int length = 0; // ��ǰ�������еĳ���
	while (*p != '\0') {
		if (isExists(hashTable, *p)) {
			// ��� *p �Ѿ����ڣ���ǰλ�ú��Ѵ���λ��֮���Ƿ���ڻ�������
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
	// û���ҵ����ȴ���1�Ļ��Ĵ�
	if (length == 0) {
		// ��Ϊ���ַ��������ؿ��ַ���
		if (size == 0) {
			char* pa = (char*)malloc(1 * sizeof(char));
			pa[0] = '\0';
			return pa;
		}
		else { // ���򷵻��ַ�������Ԫ��(����Ԫ�ؾ���)
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

// ʹ�� Manacher �㷨
char* longestPalindromeWithManacher(char* s) {
	char * newS = preDealString(s);
	int newSize = getSize(newS);
	int c = 0; // ��ǰ���Ĵ��ĶԳ�����
	int r = 0; // �� c λ���ģ� ��ǰ����Ĵ����Ұ뾶
	// �����ַ����ڵ�һ���������飬�洢�Զ�Ӧ�ַ�Ϊ���ĵĻ��Ĵ��İ뾶
	int* p = (int*)malloc(sizeof(int) * newSize);
	for (int i = 1; i < newSize - 1; i++) { // ��������ĸ ^ ��Ϊ��ĸ $
		 // �� c Ϊ�ԳƵ㣬i �� iMirror ���� c �����ĶԳƵĻ��Ĵ�
		int iMirror = 2 * c - i;
		// �� i ���� c Ϊ���ģ� r Ϊ�Ұ뾶�Ļ��ĶԳ��ַ�����
		if (r > i) {
			// ������ i Ϊ�Գ����ģ���� i + �Ұ뾶(p[i]) ������ c Ϊ����, rΪ�Ұ뾶�Ļ��Ĵ���
			// �� p[i] = p[i_Mirror],
			// ����˵���ַ�����������Ҫ�ٴζ� i Ϊ���ĵĻ��Ĵ������ж�,���ǿ���֪�� p[i] ��������ڵ��� r - i
			p[i] = r - i < p[iMirror] ? r - i : p[iMirror];
		}
		else {
			p[i] = 0; // ���� p[i] = 0;
		}
		// �� i ����������չ
		while (newS[i + 1 + p[i]] == newS[i - 1 - p[i]]) {
			p[i] ++;
		}
		// �� i ���е�������չ���Ұ뾶����Ѿ����� r,���µĶԳ�������Ϊ i, �Գư뾶��Ϊ i + p[i]
		if (i + p[i] > r) {
			c = i;
			r = i + p[i];
		}
	}

	// �ҳ���� index �� �뾶
	int longestIndex = 0; 
	int longest = 0;
	for (int i = 1; i < newSize - 1; i++) {
		if (p[i] > longest) {
			longestIndex = i;
			longest = p[i];
		}
	}

	int begin = (longestIndex - longest) / 2; // ������չ����������Ҫ / 2
	int end = begin + longest; // ������չ��������ֻ��һ�뼴��
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