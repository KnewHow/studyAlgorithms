# Wildcard Matching

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
```



Example 2:

```
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
```



Example 3:

```
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
```



Example 4:

```
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
```



Example 5:

```
Input:
s = "acdcb"
p = "a*c?b"
Output: false
```



来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/wildcard-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

## 解法一：纯递归

这道题目和之前做过的**正则表达式匹配**有些类似，我们可以使用递归的方法：

* 如果当前的字符是 *
  	1. 我们让 * 匹配一个字符然后比较下一个
   	2. 或者我们跳过 *，继续比较 * 的下一个和字符串s
* 如果当前的字符不是 *，我们比较当前字符(对于 ? 区分对待)是否匹配已经下个字符是否匹配。



代码如下：

```c
int isMatch(char* s, char* p) {
	if (*s == '\0') {
		// 如果 s 为空， 如果 p 为空，或者剩下的 p 都是 * 匹配成功
		// 否则失败
		while (*p != '\0') {
			if (*p != '*') {
				return 0;
			}
			p++;
		}
		return 1;
	}
	else {
		if (*p == '*') {
			return isMatch(s, p + 1) || isMatch(s + 1, p);
		}
		else {
			int firstMatch = (*s == *p) || (*p == '?');
			return firstMatch && isMatch(s + 1, p + 1);
		}
	}
}
```

但是由于频繁递归，在测试用例:

```
"aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba"
"a*******b"
```

会超时。

## 解法二：使用动态规划来优化递归

我们看看能不能使用之前动态规范的方法进行优化。超时的原因是频繁进行递归，对于之前算过的结果又重新进行了递归计算。因此我们可以构建一个二维数组`res[i][j]` 表示`s`中第`i`个字符和`p`中第`j`个字符是否匹配，这样我们只要将`res[i][j]` 填充完毕，当再次递归到相同结果使，直接根据`res`返回。

代码如下：

```c

/**
* 匹配
* @param s 原字符 s
* @param p 模式字符串 p
* @param n s 的 size
* @param m p 的 size
* @param sIndex 当前比较到 s 中的那个角标
*/
int match(
	char* s,
	char* p,
	int n,
	int m,
	int sIndex, 
	int pIndex, 
	int **res) {
	// 如果已经计算过，直接返回
	if (*(*(res + sIndex) + pIndex) != -1) {
		return *(*(res + sIndex) + pIndex);
	}
	else {
		int r = 0;
		// s 已经结束，如果 p 结束或者 p 剩下的都是 *，则匹配成功
		if (sIndex == n) {
			if (pIndex == m) { // p 也结束
				r = 1;
			}
			else {
				r = 1;
				while (*(p + pIndex) != '\0') {
					if (*(p + pIndex) != '*') {
						r = 0;
						break;
					}
					pIndex++;
				}
			}
		}
		else {
			if (*(p + pIndex) == '*') {
				r = match(s, p, n, m, sIndex, pIndex + 1, res)
					|| match(s, p, n, m, sIndex + 1, pIndex, res);
			}
			else {
				int firstMathch = *(p + pIndex) == *(s + sIndex) ||
					*(p + pIndex) == '?';
				r = firstMathch && match(s, p, n, m, sIndex + 1, pIndex + 1, res);
			}
		}
		*(*(res + sIndex) + pIndex) = r;
		return r;
	}
	

}

void freeRes(int** res, int size) {
	for (int i = 0; i < size; i++) {
		int* arr = *(res + i);
		if (arr != NULL) {
			free(arr);
		}
	}
	free(res);
}

int isMatch(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int rows = n + 1;
	int cols = m + 1;
	int** res = (int**)malloc(sizeof(int*) * rows);
	for (int i = 0; i < rows; i++) {
		int* arr = (int*)malloc(sizeof(int) * cols);
		for (int j = 0; j < cols; j++) {
			*(arr + j) = -1;
		}
		*(res + i) = arr;
	}
	int r = match(s, p, n, m, 0, 0, res);
	freeRes(res, rows);
	return r;
}
```

由于我们只要把`res`填满即可，设`s`的 size 为 `n`,`p`的 size 为 `m`，则时间复杂度为`O(n*m)`

执行测试用例消耗了**40ms**,击败了**46.37**的用户，看来似乎还有更快的方法。