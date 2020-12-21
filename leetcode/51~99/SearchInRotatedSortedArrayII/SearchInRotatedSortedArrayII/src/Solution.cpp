#include "Solution.h"

bool Solution::search(std::vector<int>& nums, int target)
{
	if (nums.size() < 1) {
		return false;
	}
	std::vector<int> s;
	int pivotIndex = -1;
	for (int i = 0; i < nums.size() - 1; i++) {
		if (nums[i] > nums[i + 1]) {
			pivotIndex = i;
			break;
		}
	}

	if (pivotIndex != -1) {
		for (int i = pivotIndex + 1; i < nums.size(); i++) {
			s.push_back(nums[i]);
		}
		for (int i = 0; i <= pivotIndex; i++) {
			s.push_back(nums[i]);
		}
	}
	else {
		s = nums;
	}
	
	int left = 0, right = s.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (target == s[mid]) {
			return true;
		}
		else if (target > s[mid]) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return false;
}
