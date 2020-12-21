# 60. Permutation Sequence

The set [1,2,3,...,n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

"123"
"132"
"213"
"231"
"312"
"321"
Given n and k, return the kth permutation sequence.

Note:

Given n will be between 1 and 9 inclusive.
Given k will be between 1 and n! inclusive.
Example 1:

Input: n = 3, k = 3
Output: "213"
Example 2:

Input: n = 4, k = 9
Output: "2314"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutation-sequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：利用全排列求第 kth 个排列

还记得我们之前的[全排列](https://github.com/KnewHow/studyAlgorithms/tree/master/leetcode/1~50/Permutations/Permutations)吗,我们可以利用这样的思路，直到计算出第k个排列，代码如下：

```c++
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    string vectorToString(vector<int> nums) {
        string r = "";
        for (auto begin = nums.begin(); begin != nums.end(); begin++) {
            string t = to_string(*begin);
            r += t;
        }
        return r;
    }
    void swapE(vector<int>& v, int i, int j) {
        int temp = v.at(i);
        v.at(i) = v.at(j);
        v.at(j) = temp;
    }
    string doPermutate(vector<int> nums, int k) {
        int kth = 1;
        while (kth < k) {
            int nth = -1;
            for (int i = 0; i < nums.size() - 1; i++) {
                if ( nums.at(i) < nums.at(i + 1)) {
                    nth = i;
                }
            }
            if (nth == -1) {
                break;
            }
            else {
                int min = nums.at(nth + 1);
                int pos = nth + 1;
                for (int i = nth + 1; i < nums.size(); i++) {
                    if (nums.at(i) > nums.at(nth) && nums.at(i) <= min) {
                        min = nums.at(i);
                        pos = i;
                    }
                }
                swapE(nums, nth, pos);
                int mid = (nth + 1 + nums.size()) / 2;
                for (int i = nth + 1; i < mid; i++) {
                    int _i = nums.size() + nth - i;
                    swapE(nums, i, _i);
                }
            }
            kth++;
        }
        return vectorToString(nums);
    }

    string getPermutation(int n, int k) {
        vector<int> nums = vector<int>();
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }
        return doPermutate(nums, k);
    }
};
```

但是最后超时了，因此如果每次都求最后一个序列，则需要`O(N!)`的时间复杂度，超时也正常。



## 解法二：阶乘数系统

参考[官方题解](https://leetcode-cn.com/problems/permutation-sequence/solution/di-k-ge-pai-lie-by-leetcode/),这里应该是第三个关于全排列的问题了，关于如何求全排列或者下一个字典序，我们之前都有方法，但是如何快速的求出第`ktn`个全排列，这里给出了一个比较好的方法，代码如下：

```c++
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    
    string getPermutation(int n, int k) {
        vector<int> nums = vector<int>();
        vector<int> factorials = vector<int>();
        factorials.push_back(1);
        for (int i = 1; i < n; i++) {
            int v = factorials.at(i - 1) * i;
            factorials.push_back(v);
        }
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }
        k--;
        string r = "";
        for (int i = n - 1; i >= 0; i--) {
            int idx = k / factorials.at(i);
            k -= idx * factorials.at(i);
            r += to_string(nums.at(idx));
            nums.erase(nums.begin() + idx);
        }
        return r;
    }
};
```

这里为我们提供了一个在`O(N^2)`内计算出第`kth`个排列的方法，作为全排列的第三种方法，我们以后可以直接用。