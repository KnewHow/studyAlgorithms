# Question

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

You may return the answer in any order.

 

Example 1:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
Example 2:

Input: n = 1, k = 1
Output: [[1]]


Constraints:

1 <= n <= 20
1 <= k <= n
通

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combinations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

我们按照较小元素在前，较大元素在后的顺序，对于n个元素的k个排列，我们第一个元素可以取：`1~n-k+1`任意一个，如果第一个元素取`kth, 1<=kth<n-k+1`,那么第二个元素可以随机的取`n-k~n`任意一个元素，为此，我们可以递归的执行。