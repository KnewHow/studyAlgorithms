#include<stdio.h>
#include<stdlib.h>

/**
* ����������ҵ�����ķֽ����أ� ����֪�������� nums ������������������˵
* ���� a[i] < a[i+1],���Ƕ��ڷֽ�� j ��˵������� a[j] > a[j+1]
* ���ǵ�Ȼ���Ա���һ�� nums ���飬�ҵ� a[j] > a[j+1] �ĵ�,
* ����������ʱ�临�ӶȾ��� O(N),�޷��ﵽ��ĿҪ���O(logN),��û�и���ķ���?
* 
* ����һ�����ǵĶ��ֲ��ҵ�˼·�������ȶ���һ�� pivot = (begin + end) / 2
* ��� nums[pivot] > nums[pivot+1],˵���� povit �����鱻�ֳ��������顣
* ����������Ҫ�Ƚ� nums[pivot] > nums[begin]����� a[pivot] > nums[begin]
* ˵�� pivot ���ڵ�һ������������ڣ��ֽ�����Ұ�ߣ��� begin = pivot
* ����˵�� pivot �Ѿ��ڵڶ������������ڣ��ֽ�������ߣ��� end = pivot
*
* �ڴ˺����У����Ƿ��طֽ�����СԪ�صĽǱ�
*/
int findSmallestIndex(int* nums, int size) {
	int begin = 0;
	int end = size - 1;
	// ��� nums[0] < nums[size-1],˵�����鱾���������ģ�ֱ�ӷ��� 0
	if (*(nums + begin) <= *(nums + end)) {
		return 0;
	}
	else {
		while (begin <= end) {
			int pivot = (begin + end) / 2;
			if (*(nums + pivot) >= *(nums + pivot + 1)) {
				return pivot + 1;
			}
			else if (*(nums + pivot) > * (nums + begin)) {
				begin = pivot;
			}
			else {
				end = pivot;
			}
		}
		return -1;
	}
}

// ��������
int binarySearch(int* arr, int begin, int end, int target) {
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (target  == *(arr + mid)) {
			return mid;
		}
		else if (target < *(arr + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	return -1;
}

/**
* ���� nums ������˵��������������������鹹�ɣ�������ǿ����ҵ���������ķֽ���
* ��ô���ǾͿ������ж� target ���ĸ����鷶Χ�ڣ�Ȼ�����ö��ֲ��ҿ��ٵĲ��ҳ�����
*
*/
int search(int* nums, int numsSize, int target) {
	if (numsSize == 0) {
		return -1;
	}
	else {
		int smallestIndex = findSmallestIndex(nums, numsSize);
		if (smallestIndex == 0) {
			return binarySearch(nums, 0, numsSize - 1, target);
		}
		else {
			int firstBegin = 0;
			int firstEnd = smallestIndex - 1;
			int secondBegin = smallestIndex;
			int secondEnd = numsSize - 1;
			// ��� target �ڵ�һ����������ķ�Χ�ڣ���ô���ڵ�һ��������ʹ�ö��ֲ�������
			if (target >= *(nums + firstBegin) && target <= *(nums + firstEnd)) {
				return binarySearch(nums, firstBegin, firstEnd, target);
			}
			// ͬ���ڵڶ������鷶Χ�ڣ��Եڶ���������ж�������
			else if (target >= *(nums + secondBegin) && target <= *(nums + secondEnd)) {
				return binarySearch(nums, secondBegin, secondEnd, target);
			}
			else {
				return -1;
			}
		}
	}
}

int main() {
	int arr[] = { 4,5,1,2,3 };
	int size = sizeof(arr) / sizeof(int);
	int target = 1;
	int r = search(arr, size, target);
	printf("r is: %d\n", r);
	system("pause");
	return 0;
}