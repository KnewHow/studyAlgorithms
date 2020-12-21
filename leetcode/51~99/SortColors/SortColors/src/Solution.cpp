#include "Solution.h"

void Solution::sortColors(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end());
}

void Solution::sortColors2(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end(),
		[](const int a, const int b)->bool {
			return a < b;
		});
}

void Solution::sortColors3(std::vector<int>& nums)
{
	quickSort(nums);
}



void Solution::sortColors4(std::vector<int>& nums)
{
	int redCounter = 0;
	int whiteCounter = 0;
	int blueCounter = 0;
	for (int n : nums) {
		if (n == 0) {
			redCounter++;
		}
		else if (n == 1) {
			whiteCounter++;
		}
		else {
			blueCounter++;
		}
	}
	int i = 0;
	int counter = redCounter;
	while (counter > 0) {
		nums[i++] = 0;
		counter--;
	}
	counter = whiteCounter;
	while (counter > 0) {
		nums[i++] = 1;
		counter--;
	}
	counter = blueCounter;
	while (counter > 0) {
		nums[i++] = 2;
		counter--;
	}
}

void Solution::quickSort(std::vector<int>& nums)
{
	quickSortR(nums, 0, nums.size() - 1);
}

void Solution::quickSortR(std::vector<int>& nums, int left, int right)
{
	if (right - left > 0) {
		int pivod = nums[left];
		int i = left;
		int j = right;
		while (i < j) {
			while (nums[j] >= pivod && i < j) {
				j--;
			}
			while (nums[i] <= pivod && i < j) {
				i++;
			}
			int temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}
		int temp = nums[left];
		nums[left] = nums[i];
		nums[i] = temp;
		quickSortR(nums, left, i - 1);
		quickSortR(nums, j + 1, right);
	}
}