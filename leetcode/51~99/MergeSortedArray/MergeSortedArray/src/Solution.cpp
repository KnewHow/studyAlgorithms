#include "Solution.h"

void Solution::merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
{
	if (m == 0) {
		nums1 = nums2;
		return;
	}
	if (n == 0) {
		return;
	}

	if (nums2[0] >= nums1[m - 1]) {
		nums1.resize(m);
		nums1.reserve(m + n);
		nums1.insert(nums1.end(), nums2.begin(), nums2.end());
		return;
	}
	if (nums1[0] >= nums2[n - 1]) {
		nums1.resize(m);
		nums2.reserve(m + n);
		nums2.insert(nums2.end(), nums1.begin(), nums1.begin() + m);
		nums1 = nums2;
		return;
	}
	
	std::vector<int> temp;
	temp.reserve(m + n);
	int i = 0, j = 0;
	while (i < m && j < n) {
		if (nums1[i] < nums2[j]) {
			temp.push_back(nums1[i]);
			i++;
		}
		else {
			temp.push_back(nums2[j]);
			j++;
		}
	}

	while (i < m) {
		temp.push_back(nums1[i]);
		i++;
	}
	while (j < n) {
		temp.push_back(nums2[j]);
		j++;
	}
	nums1 = temp;
}
