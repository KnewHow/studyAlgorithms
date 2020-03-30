# Question

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word (last word means the last appearing word if we loop from left to right) in the string.

If the last word does not exist, return 0.

Note: A word is defined as a maximal substring consisting of non-space characters only.

Example:

```
Input: "Hello World"
Output: 5
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/length-of-last-word
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

从后面往前搜索字符串，直到遇到一个空格或者字符首字符。

```c++
#include<string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s.empty()) {
            return 0;
        }
        else {
            int size = 0;
            // 是否出现了第一个非空格的字符
            bool isAlphabet = false;
            for (auto end = s.end() - 1; end >= s.begin(); end--) {
                char c = *end;
                if (c == ' ' && !isAlphabet) {
                    continue;
                }
                if (c == ' ' && isAlphabet) {
                    return size;
                }
                else {
                    isAlphabet = true;
                    size++;
                }
                if (end == s.begin()) {
                    break;
                }
            }
            return size;
        }
    }
};
```

