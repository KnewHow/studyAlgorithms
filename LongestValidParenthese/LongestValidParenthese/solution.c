#include<stdlib.h>
#include<stdio.h>

/**
* ���Ƕ�������ָ��`left`��`right`,
* һ��ʼ�ֱ�ָ���ַ����Ŀ�ͷ�����`left!=')'`��ʼ��`right`������
* ����`(`, ��`leftParenthesesSum ++������`), ��`rightParenthesesSum++`
* ���������ȣ�˵���Ҵ�һ���Ϸ��ģ���¼`leftParenthesesSum `��ֵ,
* ���`leftParenthesesSum  > rightParenthesesSum`,
* ������`right++`����ʾ�п����ҵ�`)`ʹ�ö����`(`�պϣ�
* ���`leftParenthesesSum  < rightParenthesesSum`,��ʾ�޷�ʹ�ö����`)`�պϣ�
* ��`leftParenthesesSum `��`leftParenthesesSum `��գ�
* ��`left`���������ߣ�ֱ��`left`�ٴε���`(`
* 
* ����ֻ�ǵ����Ĵ����ұ��������� `(()` �������޷�����ģ�
* Ȼ�����෴��˼·�����������һ��
*/
void getMax(char* s, int *max) {
	// �ȴ�������ɨ��һ��
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
				// �� rightParenthesesSum <= leftParenthesesSum
				if (leftParenthesesSum == rightParenthesesSum) {
					if (leftParenthesesSum > *max) {
						*max = rightParenthesesSum;
					}
				}
				right++;
			}
			// ѭ���˳����� rightParenthesesSum > leftParenthesesSum �����ַ�������
			leftParenthesesSum = 0;
			rightParenthesesSum = 0;
			left = right;
		}
	}

	// Ȼ���������ɨ��һ��
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