# Word Search

Given an m x n board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:

![](https://assets.leetcode.com/uploads/2020/11/04/word2.jpg)

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true



Example 2:

![](https://assets.leetcode.com/uploads/2020/11/04/word-1.jpg)

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true



Example 3:

![](https://assets.leetcode.com/uploads/2020/10/15/word3.jpg)

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false


Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 200
1 <= word.length <= 10^3
board and word consists only of lowercase and uppercase English letters.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-search
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

我们可以使用回溯法。首先找到单词首字母出现的所有位置，然后从这些位置开始搜索。一个字母有`2~4`个方向可以搜索，我们用0代表向右搜索，1为向下搜索，2为向左搜索，3为向上搜索，我们用一个和目标矩阵相同的矩阵来表示当前元素寻找方向，初始值都为-1，表示没有开始搜索。

我们找到第一个字母出现的位置，判断该位置可以进行那些方向的探索，我们依次进行。对于第`a[i][j]`个元素，我们先让其向右探索，如果右边的元素等于第二个字母，继续，否则换一个地方探索，直到所有的方向都探测完毕。如果所有的方向探测完毕也找不到我们需要的目标字母，则进行回溯。找到上一个探索的位置，从上一次探索的方向的下一个方向继续探索。如果第一个字母所在的所有方向都以探索完毕，都找不到符合的路径，则返回false，继续从下一个首字母出现的位置开始，直到有成功的路径或者所有首字母出现的位置都探索完毕。

思路虽然是对的，但是代码没写出来，看了一下别人的题解，果然精髓，我得研究研究才行：https://leetcode-cn.com/problems/word-search/solution/zai-er-wei-ping-mian-shang-shi-yong-hui-su-fa-pyth/