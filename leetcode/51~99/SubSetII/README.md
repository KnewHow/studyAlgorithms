# SubSet II

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

Example:

Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

## s1 老的组合方法+unorder_map 去重算法

`Solution.h`:

```c++
#pragma once
#include<vector>
#include<unordered_set>
#include<algorithm>

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

using MySet = std::unordered_set<std::vector<int>, VectorHash>;

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);
    
    void doCombine(std::vector<int>& nums, MySet& res, int k, int previousIndex, int kth, std::vector<int>& tmp);
};


```

`Solution.cpp`

```c++
#include "Solution.h"

std::vector<std::vector<int>> Solution::subsetsWithDup(std::vector<int>& nums)
{
	MySet res;
	std::vector<int> temp = {};
	for (int i = 1; i <= nums.size(); i++) {
		doCombine(nums, res, i, -1, 0, temp);
	}
	std::vector<std::vector<int>> r = std::vector<std::vector<int>>(res.begin(), res.end());
	r.push_back({});
	return r;
}

void Solution::doCombine(std::vector<int>& nums, MySet& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // 取到k个
		std::vector<int> v = tmp;
		std::sort(v.begin(), v.end()); // 复制并排序，让相同组合不同顺序的结果Hash值相同
		res.insert(v);
		return;
	}

	// 如果剩下的元素不足以构成组合，直接舍去
	if (k - kth > nums.size() - previousIndex - 1) {
		return;
	}

	for (int i = previousIndex + 1; i < nums.size(); i++) {
		tmp.push_back(nums[i]);
		doCombine(nums, res, k, i, kth + 1, tmp);
		tmp.pop_back();
	}
}
```

运行效率还算可以，只是多了很多冗余的排序和去重，能不能有直接去重的算法？



## s2 排序+去重 算法

`Solution.h`

```c++
#pragma once
#include<vector>
#include<algorithm>

class Solution {
public:
    
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums);
    void doCombine_DeleteRepeat(const std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp);
};
```

`Solution.cpp`

```c++
std::vector<std::vector<int>> Solution::subsetsWithDup(std::vector<int>& nums)
{
	std::vector<std::vector<int>> res;
	res.push_back({});
	std::vector<int> temp;
	std::sort(nums.begin(), nums.end()); // 排序，防止元素错序导致跳过失败
	for (int i = 1; i <= nums.size(); i++) {
		doCombine_DeleteRepeat(nums, res, i, -1, 0, temp);
	}
	return res;
}

void Solution::doCombine_DeleteRepeat(const std::vector<int>& nums, std::vector<std::vector<int>>& res, int k, int previousIndex, int kth, std::vector<int>& tmp)
{
	if (kth == k) { // 取到k个
		res.push_back(tmp);
		return;
	}

	// 如果剩下的元素不足以构成组合，直接舍去
	if (k - kth > nums.size() - previousIndex - 1) {
		return;
	}
	int previousElement = 0;
	for (int i = previousIndex + 1; i < nums.size(); i++) {
		if (i == previousIndex + 1) {
			previousElement = nums[i];
			tmp.push_back(nums[i]);
			doCombine_DeleteRepeat(nums, res, k, i, kth + 1, tmp);
			tmp.pop_back();
		}
		else {
			if (previousElement == nums[i]) {// same position can't put same element twice, do nothing here
				continue;
			}
			else {
				previousElement = nums[i];
				tmp.push_back(nums[i]);
				doCombine_DeleteRepeat(nums, res, k, i, kth + 1, tmp);
				tmp.pop_back();
			}
		}
		
	}
}
```

