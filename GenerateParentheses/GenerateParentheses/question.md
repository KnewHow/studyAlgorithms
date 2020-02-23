# Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/generate-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

对于给定的`n`组小括号，我们知道肯定有`n`个`(`和`n`个`)`,则我们可以把问题转换为：如何在`n`个`(`中插入剩下`n`的`)`，当然对于第`i`个`(`,我们最多能插入`i`个`)`,这还是前面都没插入的情况。例如当n=3是，我们有是三个`(((`,在第一个`(`后面我们可以插入0或者1个`)`,记为`ki`,还剩下`n-ki`个，在第二个`(`后面，我们做多可以插入两个`)`这还取决于它前面还插入了多少个`)`,例如前面插入b个，则，最多只能插入`i-b`个，因此可以分解为如下的递归函数：

```c

/**
* @param i 当前第i个(后面
* @param 总共有n 个 (
* @param arr 当前的结果数组
* @param used 当前已经使用的 )
* @param left 当前剩余的 )
*/
void generate(int i, int n, int *arr, int used,int left) {
    // 我们只有计算到 n-1 ( 个即可，因为第 n 个后面剩下多少就是多少
    if(i < n) { 
        // 第 i 个 ( 后面最多可以有 i - used 个 arr
        for(int i = 0; i <= i-used; i++) {
            // 每次递归 i自增， n 不变， arr + 1 表示将之前的结果和现在的进行合并，这里是伪代码
            // 消耗数 = 之前消耗 + 当前消耗
            // 剩余数 = 之前剩余 - 当前消耗
            generate(i + 1, n, arr + i, used+i, leff-i);
        }
    } else {
        // 到第n个，说明已经到了最后一个，把剩下的作为最后一个后面的 ) 即可
        // 伪代码
        int * r = arr + left;
        // 现在已经有了 n 个(，和每个( 后面有多少个 ),我们可以根据这些数据构建一个完整的字符串
        result[size++] = toString(r);
    }
}
```

上述的代码使用 C 语言实现时，会产生莫名其妙的错误：

```c
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
			if (nth == 2) {
				printf("nth=%d\n", nth);
			}
			if (nth == 3) {
				printf("nth=%d\n", nth);
			}
			// 合并前面的结果
			while (j < nth - 1) {
				*(newResult + j) = *(preResult + j);
				j++;
			}
			printf("\n");
			// 合并当前的结果
			*(newResult + j) = i;
			printArr(preResult, nth-1);
			printArr(newResult, nth);
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
		int j = 0;
		// 合并前面的结果
		while (j < nth - 1) {
			*(newResult + j) = *(preResult + j);
			j++;
		}
		// 合并当前的结果
		*(newResult + j) = left;
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
```

但是使用 Java 代码写却通过了测试，有没有哪位精通 C 的大神，告诉我问题出现在哪:

```java
import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

public class Solution {

	List<String> results = new ArrayList<String>();
	
	public String generateString(List<Integer> list) {
		StringBuilder sb = new StringBuilder();
		for(Integer times : list) {
			sb.append("(");
			for(int i = 0; i < times; i++) {
				sb.append(")");
			}
		}
		return sb.toString();
	}

	/**
	* @param nth 当前第nth个(后面
	* @param 总共有 n 个 (
	* @param preResult 当前的结果数组
	* @param used 当前已经使用的 )
	* @param left 当前剩余的 )
	*/
	public void generate(
		int nth, 
		int n, 
		List<Integer> preResult, 
		int used, 
		int left) {
		if(nth < n) {
			for(int i = 0;i <= nth-used; i++) {
				List<Integer> newResult = new ArrayList<Integer>(preResult);
				newResult.add(i);
				generate(nth + 1, n, newResult, used + i, left -i);
			}
		} else {
			List<Integer> newResult = new ArrayList<Integer>(preResult);
			newResult.add(left);
			results.add(generateString(newResult));
		}
	}

	public List<String> generateParenthesis(int n) {
		generate(1, n, new ArrayList<Integer>(), 0, n);
		return results;

	}

	@Test
	public void test() throws InterruptedException {
		List<String> r =  generateParenthesis(11);
		System.out.println("r size is:" + r.size());
		for(String s: r) {
			System.out.println(s);
		}
		
	}
}

```

