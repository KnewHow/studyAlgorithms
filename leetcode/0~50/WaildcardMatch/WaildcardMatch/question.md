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



## 解法三：纯动态规划算法

参考[官方题解](https://leetcode-cn.com/problems/wildcard-matching/solution/tong-pei-fu-pi-pei-by-leetcode/)的解法二，我们知道，在匹配过程中，我们可以不断的利用之前已经匹配的结果。设`s`的长度为`n`, p 的长度为`m`,则我们建立一个辅助数组`res[m+1][n+1]`，其中 `res[i][j]` 表示 `p` 中第 `i`个字符和`s` 中第 `j` 个字符的匹配情况， 1-匹配，0-不匹配。特别地 `res[0][0]=1` 表示开头的两个空字符串匹配成功，然后有如下匹配规则：

* 如果当前`p[i-1] ==  '*'` 表示 `p` 可以匹配任意多个字符，但是我需要找到 上一个匹配成功的位置`res[i-1][j]`，然后从`res[i][j]` 开始一直到 `res[i][n]` 都匹配成功，如果上一次一个都没成功，则这次也不会匹配成功
* 如果当前 `p[i-1] == '?'`，表示匹配任意单个字符，如果上个匹配成功，这个就匹配成功，因此`res[i][j] = res[i-1][j-1]`
* 如果`p[i-1]` 不是上面两个，表示是正常的字符，则比较`p[i-1]` 和 `s[i-1]` 的值并且和上次的比较结果做 && 运算。因此`res[i][j] = s[i-1] == p[i-1] && res[i-1][j-1]`

官方题解中有具体的图例说明，看不懂代码的人可以去看看，尤其是下面这段代码，我加了我自己的注释：

```c
if (*(p + i - 1) == '*') {
    int sSize = 1;
    /* 找出之前成功匹配的一个点，如果之前都没有成功匹配，则 sSize = n+1，
	*  此时 res[i][n] = 0, 表示之前的匹配失败，则当前行 res[i][*] 全为 0
	*  若之前有匹配成功的 res[i-1][sSize-1] 项，
    *  则由于是 * 的关系，当前的 res[i][sSize-1] 可以理解为 * 和空字符匹配成功，后面的都匹配成功
    */
    while (*(*(res + i - 1) + sSize - 1) != 1 && sSize < n + 1) {
        sSize++;
    }
    *(*(res + i) + sSize - 1) = *(*(res + i - 1) + sSize - 1);
    while (sSize < n + 1) {
        *(*(res + i) + sSize) = 1;
        sSize++;
    }
}
```

完整的代码如下：

```c
void freeRes(int** res, int size) {
	for (int i = 0; i < size; i++) {
		int* arr = *(res + i);
		if (arr != NULL) {
			free(arr);
		}
	}
	free(res);
}

int isMatch3(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int** res = (int**)malloc(sizeof(int*) * (m + 1));
	for (int i = 0; i < m + 1; i++) {
		int* arr = (int*)malloc(sizeof(int) * (n + 1));
		for (int j = 0; j < n + 1; j++) {
			*(arr + j) = 0;
		}
		*(res + i) = arr;
	}
	*(*(res + 0) + 0) = 1;
	for (int i = 1; i < m + 1; i++) {
		if (*(p + i - 1) == '*') {
			int sSize = 1;
			/* 找出之前成功匹配的一个点，如果之前都没有成功匹配，则 sSize = n+1，
			*  此时 res[i][n] = 0, 表示之前的匹配失败，则当前行 res[i][*] 全为 0
			*  若之前有匹配成功的 res[i-1][sSize-1] 项，
			*  则由于是 * 的关系，当前的 res[i][sSize-1] 可以理解为 * 和空字符匹配成功，后面的都匹配成功
			*/
			while (*(*(res + i - 1) + sSize - 1) != 1 && sSize < n + 1) {
				sSize++;
			}
			*(*(res + i) + sSize - 1) = *(*(res + i - 1) + sSize - 1);
			while (sSize < n + 1) {
				*(*(res + i) + sSize) = 1;
				sSize++;
			}
		}
		else if (*(p + i - 1) == '?') { // 如果为 ？，则之前的匹配，现在的也匹配
			for (int sSize = 1; sSize < n + 1; sSize++) {
				*(*(res + i) + sSize) = *(*(res + i - 1) + sSize - 1);
			}
		}
		else { // 如果不为 * 或者 ?，此时需要比较当前的 p[i-1] 和 s[sSize-1]的值，以及之前的比较结果
			for (int sSize = 1; sSize < n + 1; sSize++) {
				*(*(res + i) + sSize) = *(p + i - 1) == *(s + sSize - 1) 
					&& *(*(res + i - 1) + sSize - 1);
			}
		}
	}
	int r = *(*(res + m) + n);
	freeRes(res, m + 1);
	return r;
}
```



## 解法四：回溯法

参考[官方题解](https://leetcode-cn.com/problems/wildcard-matching/solution/tong-pei-fu-pi-pei-by-leetcode/)的解法三，我们让`s` 和 `p` 逐一比较，我们可以让 `*` 匹配 0，1，2 ... 个字符，我们先从 0 个字符开始，如果后面发现无法匹配且前面有 * 时，我们让其回溯，代码如下：

```c
/**
* 回溯法
*/
int isMatch4(char* s, char* p) {
	int n = strlen(s);
	int m = strlen(p);
	int i = 0;
	int j = 0;
	int starIndex = -1; // 记录 p 中 * 角标
	int sTempIndex = -1; // 当 * 出现时， s 的对应角标
	while (i < n) {
		if (j < m && *(p + j) == '?' || *(p + j) == *(s + i)) {
			i++;
			j++;
		}
		else if (j < m && *(p + j) == '*') {
			starIndex = j;
			sTempIndex = i;
			j++;
		}
		else if (starIndex == -1) { // 在不匹配的情况下，有没有 * 可以回溯，直接返回 false
			return 0;
		}
		else { 
			j = starIndex + 1;
			i = sTempIndex + 1;
			sTempIndex = i;
		}
	}
	// 如果 s 结束时，如果 j 结束或者 j 后面都为 *,则匹配成功,否则匹配失败
	for (int k = j; k < m; k++) {
		if (*(p + k) != '*') {
			return 0;
		}
	}
	return 1;
}
```

时间复杂度：最好的情况下是O(min(S, P))，平均情况下是O(SlogP)，其中 S 和 P 指的是字符模式和输入字符串的长度。详细证明可点击：[证明过程](https://arxiv.org/pdf/1407.0950.pdf)。

既聪明有又空间的做法，证明过程可以看看，不得了的东西。