# Unique Binary Search Tree

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/unique-binary-search-trees-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solotion

我看了题解，是这样，二叉搜索树的性质在于：根节点的值大于所有左子树的值，并且根节点的值小于所有右子树的值，并且左右子树同为二叉搜索树。有了这样的性质，我们依次可以选取`1~n`中的某个元素`i`为根节点值，这样左子树的值只能为`1~i-1`,右子树的值只能为`i+1~n`，这样递归的进行。