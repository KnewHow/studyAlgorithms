#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include"hashTable.h"

/**
* ������������ѭ����������������֮�ͣ�ȡ��� target ����������Ǹ�
*
*/
int threeSumClosestFource(int* nums, int numsSize, int target) {
	int distans = INT_MAX;
	int sum = 0;
	for (int x = 0; x < numsSize; x++) {
		for (int y = x + 1; y < numsSize; y++) {
			for (int z = y + 1; z < numsSize; z++) {
				int s = nums[x] + nums[y] + nums[z];
				int dis = abs(target - s);
				if (dis < distans) {
					distans = dis;
					sum = s;
				}
			}
		}
	}
	return sum;
}



/**
* ��������ĵݹ���ú���
* @param nums ����������
* @param begin ���鿪ʼ�Ǳ�
* @param end ��������Ǳ�
*/
void quickSortR(int* nums, int begin, int end) {
	if (end - begin > 0) { // �������Ԫ�س�������ʱ�Ž�������
		int left = begin;
		int right = end;
		int pivot = nums[begin]; // �õ�һ��Ԫ�ص���Ԫ
		while (left < right) {
			while (*(nums + right) >= pivot && left < right) {
				right--;
			}
			while (*(nums + left) <= pivot && left < right) {
				left++;
			}
			int temp = *(nums + left);
			*(nums + left) = *(nums + right);
			*(nums + right) = temp;
		}
		int temp = *(nums + begin);
		*(nums + begin) = *(nums + left);
		*(nums + left) = temp;
		quickSortR(nums, begin, left - 1);
		quickSortR(nums, left + 1, end);
	}
}

/**
* ��������
* @param nums ԭʼ����
* @param size �����С
*/
void quickSort(int* nums, int size) {
	quickSortR(nums, 0, size - 1);
}


/**
* �ο������ϵ���⣬�������ҵļ򵥺ܶ࣬���ȶ�ԭ��������Ȼ�����
* ���������� i ��Ԫ��ʱ����ʼ�� i+1 ~ end����������е�����
* ��� sum > taget,end --������ begin++,ֱ�� begin > end
* ��Ȼʱ�临�Ӷ�Ϊ O(n^2)
* 
*/
int threeSumClosest(int* nums, int numsSize, int target) {
	quickSort(nums, numsSize);
	int sum = nums[0] + nums[1] + nums[2];
	for (int i = 0; i < numsSize; i++) {
		int begin = i + 1;
		int end = numsSize - 1;
		while (begin < end) {
			int s = nums[i] + nums[begin] + nums[end];
			if (abs(target - sum) > abs(target - s)) {
				sum = s;
			}
			if (s > target) {
				end--;
			}
			else {
				begin++;
			}
		}
	}
	return sum;
}

int main() {
	int arr[] = { -1, 2, 1, -4 };
	int size = sizeof(arr) / sizeof(int);
	int target = 1;
	int r = threeSumClosest(arr, size, target);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}