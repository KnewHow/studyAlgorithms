# Question

Given two strings s and t, return the minimum window in s which will contain all the characters in t. If there is no such window in s that covers all characters in t, return the empty string "".

Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Example 2:

Input: s = "a", t = "a"
Output: "a"


Constraints:

1 <= s.length, t.length <= 105
s and t consist of English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-window-substring
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

我们使用一个`map<char,int> target`  来保存目标字符串的字符串`t`，分别统计各字母出现的频率。再用另一个`map<char,int> window ` 来存储当前窗口中在`t`中出现的字符以及次数。我们从左边开始，依次对原始字符串`s`进行扫描。如果发现当前`window` 包含了`target`中的所有字符，我们记录一下开始的角标和长度（当然是和原先的做对比，只记录最短的角标），然后让开始的角标往后移动一位，并且如果当前开始的角标包含了`t`中的字符，需要将`window`中对应字符的数量减少一个。

算法思想参考：https://leetcode-cn.com/problems/minimum-window-substring/solution/