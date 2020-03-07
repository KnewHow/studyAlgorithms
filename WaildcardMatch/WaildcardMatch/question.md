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

会超时，我们看看能不能使用之前动态规范的方法进行优化。