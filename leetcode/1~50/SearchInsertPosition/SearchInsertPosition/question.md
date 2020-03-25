# Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Example 1:

Input: [1,3,5,6], 5
Output: 2
Example 2:

Input: [1,3,5,6], 2
Output: 1
Example 3:

Input: [1,3,5,6], 7
Output: 4
Example 4:

Input: [1,3,5,6], 0
Output: 0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-insert-position
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# Solution

二分搜索，当找不到时，比较 `a[mid]` 和 `target`的大小，如果比 `target > a[mid]`，返回`mid+1`,否则返回`mid`

```c
int searchInsert(int* nums, int numsSize, int target) {
	int begin = 0;
	int end = numsSize - 1;
	int mid = (begin + end) / 2;
	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target == *(nums + mid)) {
			return mid;
		}
		else if (target < *(nums + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	// 没找到
	if (target < * (nums + mid)) {
		return mid;
	}
	else {
		return mid + 1;
	}
}
```

