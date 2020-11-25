#include<vector>
#include "QuickSort.h"



int main() {
	std::vector<int> nums = { 2,0,2,1,1,0 };
	QuickSort::sort<int>(
		nums, 
		[](const int a, const int b)->bool {return a < b;}
	);
	// quickSort(nums);
	QuickSort::print(nums);
	std::cin.get();
}