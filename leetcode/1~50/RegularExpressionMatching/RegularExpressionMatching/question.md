# Question

Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = `"aa"`
p = `"a*"`
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
Example 3:

Input:
s = `"ab"`
p = `".*"`
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".
Example 4:

Input:
s = `"aab"`
p = `"c*a*b"`
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input:
s = `"mississippi"`
p = `"mis*is*p*."`
Output: false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/regular-expression-matching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Answer

看了官方的解答，感觉递归的力量是你无法想象的。解法使用了回溯法，对于 带 * 匹配，我们有两种情况处理：

* 忽略它，就是没有匹配上
* 和 * 匹配，然后继续和剩下的字符串进行匹配

由此可以写出如下的递归形式的代码：

```c
int isEmpty(char* s) {
	if (*s == '\0') {
		return 1;
	}
	else {
		return 0;
	}
}

int size(char* s) {
	int size = 0;
	char* p = s;
	while (*p != '\0') {
		size++;
		p++;
	}
	return size;
}

int isMatch(char* s, char* p) {
	// 如果 p 为空，判断 s 是否同时为空
	if (isEmpty(p)) {
		return isEmpty(s);
	}
	else {
		int firstMatch = !isEmpty(s) && (*s == *p || *p == '.');
		// 当模式字符串长度大于2，且p[1] == '*',我们可以作如下分析：
		// 1 直接忽略 p[0],p[1],这意味着 * 匹配 0 个字符
		// 2 或者让 * 匹配一个字符，去掉原字符串一个字符，然后使用 p 继续匹配剩下的
		if (size(p) >= 2 && *(p + 1) == '*') {
			return isMatch(s, p + 2) || (firstMatch && isMatch(s + 1, p));
		}
		else { // 如果没有 * 匹配， 第一个匹配 && 后序的匹配
			return firstMatch && isMatch(s + 1, p + 1);
		}
	}
}
```

但是这个递归调用会重复的递归的情况，因此时间复杂度也挺大的。重复递归的原因是因为我们没有存储每次递归的结果，那我们使用一个二维数组来存储每次确定的结果是不是就可以了，我们定义一个二维数组 `int arr[1024][1024]`, `i` 表示原字符才`s`中的角标，`j`表示模式字符串`p`的角标，`arr[i][j]` 表示 `s[i]` 和 `p[j]` 是否匹配，这样当第一次递归后保存其值，第二次递归再遇到，就可以直接返回，必须要继续往下递归了，于是产生如下的递归代码：

```c
// 用来存储匹配结果的数组，i` 表示原字符才`s`中的角标，`j`表示模式字符串`p`的角标，
// `arr[i][j]` 表示 `s[i]` 和 `p[j]` 是否匹配，
// 这样当第一次递归后保存其值，第二次递归再遇到，就可以直接返回，必须要继续往下递归了
int arr[1024][1024] = { 0 };

// 初始化全局数组，用 -1 来标记是否计算过
void initArray(int x, int y) {
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			arr[i][j] = -1;
		}
	}
}


/**
* 匹配字符串，使用数组保存结果,优化递归的重复计算
* @param s 原始字符串
* @param p 模式字符串
* @param i 当前比较的 s 字符串起始角标
* @param j 当前模式字符串 p 的起始角标
* @param sSize 字符串 s 的 size,传入方便作为边界判断条件
* @param pSize 字符串 p 的 size,传入方便作为边界的判断条件
* @return 此次是否匹配 1-匹配 0-不匹配
*/
int match(
	char* s, 
	char* p, 
	int i, 
	int j, 
	int sSize, 
	int pSize
) {
	// 之前已经计算过，直接返回，可以省去递归计算的次数，这也是这个算法比上面算法优化的地方
	if (arr[i][j] != -1) {
		return arr[i][j];
	}
	else { // 之前没有计算过，计算
		int r = 0;
		if (j == pSize) { // 如果 p 已经结束，看 s 有没有结束,结束返回 1,否则返回 0
			if (i == sSize) {
				r = 1;
			}
			else {
				r = 0;
			}
		}
		else {
			int firstMatch = (i != sSize) && (s[i] == p[j] || p[j] == '.');
			// j 后至少还有一个元素且 j + 1 是 *
			if (j + 1 < pSize && p[j + 1] == '*') {
				// 可以将这样的场景分为两种情况
				// 1. * 没有匹配，我们直接跳过它，比较 s 和 j + 2
				// 2. 或者 * 匹配成功，继续比较 s 的下一个是否匹配 *
				r = match(s, p, i, j + 2, sSize, pSize)
					|| (firstMatch && match(s, p, i + 1, j, sSize, pSize));
			}
			else {
				// 如果不含 * 号，第一个匹配 && 后序的匹配
				r = firstMatch && match(s, p, i + 1, j + 1, sSize, pSize);
			}
		}
		// 保存此次结果，便于后来使用
		arr[i][j] = r;
		return r;
	}
}

int isMatchWithArray(char* s, char* p) {
	int sSize = size(s);
	int pSize = size(p);
	initArray(sSize, pSize);
	return match(s, p, 0, 0, sSize, pSize);
}
```

该算法只有我们将 `arr[sSize][pSize]` 填满即可，因此时间复杂度为： `O(sSize * pSize)`