# Add Binary

Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"


Constraints:

Each string consists only of '0' or '1' characters.
1 <= a.length, b.length <= 10^4
Each string is either "0" or doesn't contain any leading zero.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-binary
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

遍历两个字符串，直接相加即可，代码如下：

```c++
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        vector<int> rv = vector<int>();
        int e1 = a.size()-1;
        int e2 = b.size()-1;
        int extra = 0; // 进位
        while (e1 >=0 || e2 >=0) {
            if (e1 >= 0 && e2 >= 0) {
                int n1 = a.at(e1) - 48;
                int n2 = b.at(e2) - 48;
                int n = n1 + n2 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e1--;
                e2--;
            }
            else if (e1 >= 0) {
                int n1 = a.at(e1)- 48;
                int n = n1 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e1--;
            }
            else {
                int n2 = b.at(e2) - 48;
                int n = n2 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e2--;
            }
        }
        if (extra > 0) {
            rv.push_back(extra);
        }
        string r = "";
        for (int j = rv.size() - 1; j >= 0; j--) {
           r += to_string(rv[j]);
        }
        return r;
    }
};
```

