#include<stdlib.h>
#include<stdio.h>
#define STRING_SIZE 10000

char* getString(char* s) {
	char* r = (char*)malloc(sizeof(char) * STRING_SIZE);
	char* p = r;
	char previous = *s;
	int counter = 1;
	s++;
	while (*s != '\0') {
		if (*s == previous) {
			counter++;
		}
		else {
			char counterC = counter + 48;
			*p++ = counterC;
			*p++ = previous;
			counter = 1;
			previous = *s;
		}
		s++;
	}
	char counterC = counter + 48;
	*p++ = counterC;
	*p++ = previous;
	*p = '\0';
	return r;
}

char* countAndSay(int n) {
	int counter = 1;
	char* s = (char*)malloc(sizeof(char) * STRING_SIZE);
	*(s + 0) = '1';
	*(s + 1) = '\0';
	while (counter < n) {
		char* s1 = getString(s);
		free(s);
		s = s1;
		counter++;
	}
	return s;
}

int main() {
	char* r = countAndSay(33);
	printf("r is: %s\n", r);
	system("pause");
	return 0;
}