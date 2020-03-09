# Permutations

Given a collection of distinct integers, return all possible permutations.

Example:

```
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## 解法一：递归法

全排列就是从原数组中随机选出一个元素，然后从剩下的元素中在选出一个，以此类推。设原数组大小为`n`,则总共有 n ! 个排列。