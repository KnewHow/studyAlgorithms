# 65. Valid Number

Validate if a given string can be interpreted as a decimal number.

Some examples:

```
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false
```



Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:

Numbers 0-9
Exponent - "e"
Positive/negative sign - "+"/"-"
Decimal point - "."
Of course, the context of these characters also matters in the input.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button to reset your code definition.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

[官方的题解](https://leetcode-cn.com/problems/valid-number/solution/biao-qu-dong-fa-by-user8973/)使用有限状态机的方法，个人觉得实在是太惊艳了，以后关于表达式判断方面的思路，可以多考虑一下这种这条机的思想。代码如下：

```c++
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    int getId(char c) {
        if (c == ' ') {
            return 0;
        }
        else if (c == '-' || c == '+') {
            return 1;
        }
        else if (c == '.') {
            return 3;
        }
        else if (c == 'e') {
            return 4;
        }
        else if (c >= '0' && c <= '9') {
            return 2;
        }
        else {
            return -1;
        }
    }
    bool isNumber(string s) {
        int states[9][5] = { 
            { 0, 1, 6, 2,-1},
            {-1,-1, 6, 2,-1},
            {-1,-1, 3,-1,-1},
            { 8,-1, 3,-1, 4},
            {-1, 7, 5,-1,-1},
            { 8,-1, 5,-1,-1},
            { 8,-1, 6, 3, 4},
            {-1,-1, 5,-1,-1},
            { 8,-1,-1,-1,-1} 
        };
        // 最终状态只有 3、5、6、8 状态才为合法状态
        int finals[] = { 0, 0, 0, 1, 0, 1, 1, 0, 1 };
        int state = 0;
        for (auto begin = s.begin(); begin != s.end(); begin++) {
            char c = *begin;
            int id = getId(c);
            if (id < 0) {
                return false;
            }
            state = states[state][id];
            if (state < 0) {
                return false;
            }
        }
        return finals[state] > 0;

    }
};
```



