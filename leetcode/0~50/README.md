# LeetCode 前 50 题的刷题心得

从2020年2月初至3月中旬，由于受疫情的影响，不能去培训 UE4，只能在家提升自己。算法一直是被我自己忽略的一个问题，在校期间沉迷 Java服务端，整天想的就是各种框架、并发、集群、分布式等高大上的东西，而忘了最基础的一些东西。记得以前在学校参加算法比赛和网易的算法比试，算法题目我几乎都做不出来。有时候我很纳闷：我明明已经认真的学习了《算法和数据结构》，怎么这些算法题我还是做不出来呢。在开始刷题以后，发现自己的水平渐渐有了提升，以前拿到题目不知怎么入手，现在也能有点思路。下面我把自己刷 [leetcode](https://leetcode-cn.com/) 前五十题的心得写一下。

## 1. 整体分析

刷完前五十题，给我的感觉就是**算法**比较重要，用到的**数据结构**比较少。只有几题涉及到链表和 HashTable，对于树、图等高等数据结构暂不涉及。对排序、查找、递归、动态规划等思想考的比较多。下面我们就来一一分析

## 2.给我留下印象比较深刻的算法

### 2.1 动态规划

动态规划在我们学校的《算法与数据结构》的书中是不涉及的，我也是从网上找些文章再结合算法导论知道它是什么东西的。对于一些算法问题，我们可以用递归法求解，例如 [Regular Expression Matching](https://leetcode-cn.com/problems/regular-expression-matching/) 和 [Wildcard Matching](https://leetcode-cn.com/problems/wildcard-matching/) 我们都是可以通过递归算法转换为先解决当前元素，然后递归的解决子问题。但有时候递归会重复的解决子问题，导致大量冗余的计算。因此既然前面已经计算出结果，我们为何不先保存一份，给后人使用呢？“牛顿之所以伟大是因为他站在巨人的肩上” 动态规划之所以出名是因为他需要使用一个`dp` (dynamic programming)数组来保持每次的结果。

### 2.2 最长回文子串

以前比试的时候，做过几道关于回文子串的算法题，当时怎么也算不出来，但是自从有了[Manacher ](https://leetcode.wang/leetCode-5-Longest-Palindromic-Substring.html) 算法，一切都不是问题了。

### 2.3 n 数之和的问题

如果你曾经对 n 数之和的问题感到恐惧，你可以尝试一下前五十题中的这些题目：

* #### [Two Sum](https://leetcode-cn.com/problems/two-sum/)

* #### [3Sum](https://leetcode-cn.com/problems/3sum/)

* #### [3Sum Closest](https://leetcode-cn.com/problems/3sum-closest/)

* #### [4Sum](https://leetcode-cn.com/problems/4sum/)

* #### [Combination Sum](https://leetcode-cn.com/problems/combination-sum/)

* #### [Combination Sum II](https://leetcode-cn.com/problems/combination-sum-ii/)

做完后，保证你有收获。

### 2.4 对于一个数组元素的全排列

前五十题中，有这么两题

* #### [Permutations](https://leetcode-cn.com/problems/permutations/)

* #### [Permutations II](https://leetcode-cn.com/problems/permutations-ii/)

当然用递归的方法很容易就完成，但是再元素有重复时，代码需要稍微的修改一下。但是我之前有做过这道题目 [Next Permutation](https://leetcode-cn.com/problems/next-permutation/)。然后我们发现对一个数组的全排列，就是求这个数组所有的字典序，由此可以得到一个通用的解法。

### 2.5 以  2^k  的速度来逼近一个数

[Pow(x, n)](https://leetcode-cn.com/problems/powx-n/) 对于这样的题目，我们当然可以从1 开始慢慢的自增到 n,但是当 n 很大的时候，这样效率比较低，因此我们可以使用翻倍法，1+1，2+2，4+4，8+8，16+16，...,这样会以 2^k 速度逼近n，当到达 n 时，需要 logN 次。

对于下面这两题，此方法仍然适用：

* #### [Divide Two Integers](https://leetcode-cn.com/problems/divide-two-integers/)

* #### [Find First and Last Position of Element in Sorted Array](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

第二题先使用二分查找，然后从查找到的位置用翻倍法逼近。

### 2.6 贪心和回溯

关于贪心和回溯算法，比较典型的是《数据结构》中的迷宫问题，但是再 [Sudoku Solver](https://leetcode-cn.com/problems/sudoku-solver/) 也用到类似的思路。每次从 1 开始尝试，如果所有的数字都不符合，说明前面有个数填写的不正确，需要回溯到最近一个可以回溯的点，以此类推的解决数独的问题。

### 2.7 寻找第 k 小的数

[Median of Two Sorted Arrays](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/) 关于如何再两个有序数组中查找第中位数的问题可以转换为找第 nth 小的数，然后利用折半排除法，可以再`O(log(m+n))`的时间复杂度内完成，可以参考[精选题解的第三种解法](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-2/)。

### 2.8 误打误撞的 KMP 算法

其实[Implement strStr()](https://leetcode-cn.com/problems/implement-strstr/)是匹配字符串子串的一种最简单的实现方式，有一种算法叫 KMP 算法，可以再 O(N) 的时间内计算子串的首次出现的位置，可以参照[这篇文章](https://zhuanlan.zhihu.com/p/83334559)，写的非常的详细。

### 2.9 关于 HashMap 得说两句

不知道大家都是拿什么语言刷题的，向我是拿 C 刷题的，因此所有的 HashMap 都要自己手写。怎么说呢，我的 Java 也挺厉害的，但是既然是学算法嘛，就不要那么浮躁啦，自己写一个又如何呢？听说 Java 中的 HashMap 再碰撞过多的时候，会将链表展成红黑树，要不去手撸一个？祈祷我可以成功，不要死在红黑树里面。下面是是几个对于 HashMap 应用的算法题：

* #### [Group Anagrams](https://leetcode-cn.com/problems/group-anagrams/)

* #### [Substring with Concatenation of All Words](https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/)

* #### [Two Sum](https://leetcode-cn.com/problems/two-sum/)

### 2.10 关于算法时间复杂度证明

一般算法的时间复杂度都比较好计算，但有的比较麻烦，例如[Wildcard Matching](https://leetcode-cn.com/problems/wildcard-matching/solution/tong-pei-fu-pi-pei-by-leetcode/)的递归解法，只是说明了一下，并没有严格的证明。其实我现在才发现，其实证明一个算法的时间复杂度也很重要，不然你无法说明你的算法比别人高效！你看看人家对第三种算法的证明，直接写了[一篇论文](https://arxiv.org/pdf/1407.0950.pdf)。有时间去读读，提升自己的英文水平也不错。

## 写在最后

其实个人觉得刷算法题最主要是练习自己对算法和数据结构的掌握和理解，不需要图快。有些题目一看到没思路，可以先放放，明天或者有空的时间再想想，不要立刻看答案，也不要死记硬背。如果自己的思路效率不高，有时间的情况下也要把它实现出来，这是锻炼你思维的一种很好的方式。还有如果觉得自己数学差，可以去补一下微积分、线性代数等知识，推荐浙江大学[苏德矿](https://www.icourse163.org/u/mooc1535616401347)的[微积分课程](https://www.icourse163.org/course/ZJU-1003315004)。我就是上午学微积分，下午刷算法题。再刷算法题的时候，总感觉有些数学的灵感时有时无的出现在你的脑海中。

那个，一百题再会啦！