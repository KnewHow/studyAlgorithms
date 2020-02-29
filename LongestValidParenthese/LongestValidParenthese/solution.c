#include<stdlib.h>
#include<stdio.h>

/**
* 我们定义两个指针`left`和`right`,
* 一开始分别指向字符串的开头，如果`left!=')'`开始让`right`自增，
* 遇到`(`, 让`leftParenthesesSum ++，遇到`), 让`rightParenthesesSum++`
* 如果二者相等，说明找打一个合法的，记录`leftParenthesesSum `的值,
* 如果`leftParenthesesSum  > rightParenthesesSum`,
* 继续让`right++`，表示有可能找到`)`使得多余的`(`闭合；
* 如果`leftParenthesesSum  < rightParenthesesSum`,表示无法使得多余的`)`闭合，
* 将`leftParenthesesSum `和`leftParenthesesSum `清空，
* 让`left`继续往下走，直到`left`再次等于`(`
* 
* 但是只是单单的从左到右遍历，对于 `(()` 类型是无法解出的，
* 然后按照相反的思路从右往左遍历一遍
*/
void getMax(char* s, int *max) {
	// 先从左往右扫描一遍
	int n = strlen(s);
	char* left = s;
	char* right = left;
	int leftParenthesesSum = 0;
	int rightParenthesesSum = 0;
	while (*left != '\0' && *right != '\0') {
		if (*left != '(') {
			left++;
		}
		else {
			right = left + 1;
			leftParenthesesSum++;
			while (leftParenthesesSum >= rightParenthesesSum
				&& *right != '\0') {
				if (*right == '(') {
					leftParenthesesSum++;
				}
				else {
					rightParenthesesSum++;
				}
				// 当 rightParenthesesSum <= leftParenthesesSum
				if (leftParenthesesSum == rightParenthesesSum) {
					if (leftParenthesesSum > *max) {
						*max = rightParenthesesSum;
					}
				}
				right++;
			}
			// 循环退出，则 rightParenthesesSum > leftParenthesesSum 或者字符串结束
			leftParenthesesSum = 0;
			rightParenthesesSum = 0;
			left = right;
		}
	}

	// 然后从右往左扫描一遍
	left = s + n - 1;
	right = left;
	leftParenthesesSum = 0;
	rightParenthesesSum = 0;
	while (left - s >= 0) {
		if (*left != ')') {
			left--;
		}
		else {
			rightParenthesesSum = 1;
			right = left - 1;
			while (right - s >= 0 
				&& rightParenthesesSum >= leftParenthesesSum) {
				if (*right == '(') {
					leftParenthesesSum++;
				}
				else {
					rightParenthesesSum++;
				}
				if (leftParenthesesSum == rightParenthesesSum) {
					if (leftParenthesesSum > * max) {
						*max = leftParenthesesSum;
					}
				}
				right--;
			}
			leftParenthesesSum = 0;
			rightParenthesesSum = 0;
			left = right;
 		}
	}
}

int longestValidParentheses(char* s) {
	int max = 0;
	getMax(s, &max);
	return max * 2;
}

int main() {
	char* s = "(()";
	int max = longestValidParentheses(s);
	printf("max is: %d\n", max);
	system("pause");
	return 0;
}