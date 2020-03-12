#include<stdlib.h>
#include<stdio.h>

/**
* �� nums �д���������������� s1,s2, �� s1,s2 �У����� s[i] < s[i+1]
* ��ô������� j ʹ�� nums[j] >= nums[j+1],�� j Ϊ nums �ķֽ�㣬
* �� j Ϊ���Ԫ�ؽǱ꣬ j+1 Ϊ��СԪ�ؽǱꡣ
* ���ǵ�Ȼ���Ա���һ�����飬�ҵ� nums[j] >= nums[j+1]������������ʱ�临�Ӷ�Ϊ O(N)
* �ܲ��ܸ���һ���أ�
* 
* ���ǿ������ö���������˼�롣�� pivot = (begin + end) / 2;
* ��� nums[pivot] >= nums[pivot + 1] ��ô pivot ��Ϊ�ֽ�㣬�������Ǽ����Ƚ�
* nums[pivot] > nums[begin]? ������ڣ�˵�����ǻ��ڵ�һ������������ڣ�����Ӧ��ȥ�ұ���
* �� begin = pivot(Ҫ֪�� pivot �ǲ��������ģ���Ϊ�����ܾ��Ƿֽ�㣬�� [5,4,1,2,3]),
* ����˵�������Ѿ����˵ڶ����������飬Ӧ������������ end = pivot
*/
int findMin(int* nums, int numsSize) {
	int begin = 0;
	int end = numsSize - 1;
	if (*(nums + begin) <= *(nums + end)) {
		return *(nums + 0);
	}
	else {
		while (begin <= end) {
			int pivot = (begin + end) / 2;
			if (*(nums + pivot) >= *(nums + pivot + 1)) {
				return *(nums + pivot + 1);
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

int main() {
	int arr[] = { 3,4,5,1,2 };
	int size = sizeof(arr) / sizeof(int);
	int min = findMin(arr, size);
	printf("min is:%d\n", min);
	system("pause");
	return 0;
}