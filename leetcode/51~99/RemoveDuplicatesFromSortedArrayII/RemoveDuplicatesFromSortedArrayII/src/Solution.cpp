#include "Solution.h"

int Solution::removeDuplicates(std::vector<int>& nums)
{
	if (nums.size() < 1) {
		return 0;
	}
	else {
		int len = nums.size();
		int currentElement = nums[0];
		int currentElementAppearTimes = 1;
		int i = 1;
		while (i < nums.size()) {
			if (currentElement == nums[i]) {
				++currentElementAppearTimes;
				if (currentElementAppearTimes > 2) {
					--len;
					// ����ǰԪ�صĺ�һλ�ƶ�����ǰԪ��
					if (i + 1 <= nums.size() - 1) {
						nums.erase(nums.begin() + i);
					}
					else {
						i++;
					}
				}
				else {
					i++;
				}
			}
			else {
				currentElement = nums[i];
				currentElementAppearTimes = 1;
				i++;
			}
		}
		return len;
	}
}
