# Plus One

Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/plus-one
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

将最低位加一，出现进位就继续加，直到进位为0，代码如下：

```c++
#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int size = digits.size();
        int extra = 1; // 进位
        for (int j = size - 1; j>=0; j--) {
            if (extra < 1) {
                break;
            }
            else {
                int n = digits.at(j);
                int newN = n + extra;
                digits.at(j) = newN % 10;
                extra = newN / 10;
            }
        }
        // 如果循环结束还有进位，表示数字扩大了一位，需要在前面+1 位
        if (extra > 0) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
    void printDigits(vector<int> digits) {
        cout << "[";
        for (auto b = digits.begin(); b != digits.end(); b++) {
            if (b == digits.end() - 1) {
                cout << *b;
            }
            else {
                cout << *b << ", ";
            }
        }
        cout << " ]" << endl;
    }
};
```

