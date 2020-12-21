# Recover Binary Tree

You are given the root of a binary search tree (BST), where exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Follow up: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

 

Example 1:

![](https://assets.leetcode.com/uploads/2020/10/28/recover1.jpg)

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:

![](https://assets.leetcode.com/uploads/2020/10/28/recover2.jpg)

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/recover-binary-search-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

我有个很变态的做法，先拿到所有节点，然后排序，最后返回一个有序的树状链表。但是好像不行。

算了，看题解，使用中序遍历然后找到两个反序的值，在递归遍历树，交换他们的位置即可。