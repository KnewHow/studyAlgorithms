#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<math.h>

// 用于存储最终结果的二维数组
char **result = NULL;
// 结果的长度
int size = 0;

/**
* 将已经获取的结果转换为对应的字符串
* @param arr 已经计算好的数组，即每个 ( 后面有多少个 )
* @param n 对小括号
*/
char* toString(int* arr, int n) {
	int total = 2 * n + 1;
	char* str = (char*)malloc(sizeof(char) * total);
	char* p = str;
	for (int i = 0; i < n; i++) {
		*p++ = '(';
		int times = *(arr + i);
		for (int j = 0; j < times; j++) {
			*p++ = ')';
		}
	}
	*p = '\0';
	return str;
}

void printArr(int * arr, int size) {
	printf("printArr strart=====\n");
	for (int i = 0; i < size; i++) {
		printf("%d, ", *(arr + i));
	}
	printf("\nprintArr end=====\n");
}

/**
* @param nth 当前第nth个(后面
* @param 总共有 n 个 (
* @param preResult 当前的结果数组
* @param used 当前已经使用的 )
* @param left 当前剩余的 )
*/
void generate(int nth, int n, int* preResult, int used, int left) {
	// 我们只有计算到 n-1 ( 个即可，因为第 n 个后面剩下多少就是多少
	if (nth < n) {
		// 第 i 个 ( 后面最多可以有 i - used 个 arr
		for (int i = 0; i <= nth - used; i++) {
			// 创建新数组来保存结果
			int* newResult = (int*)malloc(sizeof(int) * nth);
			int j = 0;
			// 合并前面的结果
			for (int j = 0; j < nth - 1; j++) {
				*(newResult + j) = *(preResult + j);
			}
			// 合并当前的结果
			*(newResult + nth - 1) = i;
			// 消耗数 = 之前消耗 + 当前消耗
			// 剩余数 = 之前剩余 - 当前消耗
			generate(nth + 1, n, newResult, used + i, left - i);
			/*if (newResult != NULL) {
				free(newResult);
			}*/
		}
	}
	else {
		// 到第n个，说明已经到了最后一个，把剩下的作为最后一个后面的 ) 即可
		int* newResult = (int*)malloc(sizeof(int) * nth);
		// 合并前面的结果
		for (int j = 0; j < nth - 1; j++) {
			*(newResult + j) = *(preResult + j);
		}
		// 合并当前的结果
		*(newResult + nth - 1) = left;
		// 现在已经有了 n 个(，和每个( 后面有多少个 ),我们可以根据这些数据构建一个完整的字符串
		*(result + size) = toString(newResult, n);
		size++;
		/*if (newResult != NULL) {
			free(newResult);
		}*/
	}
}


char** generateParenthesis(int n, int* returnSize) {
	result = (char**)malloc(sizeof(10240 * sizeof(char*)));
	generate(1, n, NULL, 0, n);
	*returnSize = size;
	return result;
}

int main() {
	int returnSize = 0;
	char** r = generateParenthesis(5, &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%s\n", *(r + i));
	}
	system("pause");
	return 0;
}