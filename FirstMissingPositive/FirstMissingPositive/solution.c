#include<stdlib.h>
#include<stdio.h>
#include<limits.h>

void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

void quickSortR(int* arr, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = *(arr + begin);
		while (left < right) {
			while (left < right && *(arr + right) >= pivot) {
				right--;
			}

			while (left < right && *(arr + left) <= pivot) {
				left++;
			}
			swap(arr, left, right);
		}
		swap(arr, begin, left);
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

int firstMissingPositive(int* nums, int numsSize) {
	quickSort(nums, numsSize);
	int begin = 0;
	while (begin < numsSize) {
		if (*(nums + begin) < 1) {
			begin++;
		}
		else {
			break;
		}
	}
	if (begin == numsSize) { // ȫ��Ϊ����
		return 1;
	}
	else {
		int counter = 1;
		for (int i = begin; i < numsSize; i++) {
			// ÿ���� counter ��������� arr[i] > counter��
			// ˵���м��и���С����������©
			if (*(nums + i) == counter) {
				counter++;
			}
			else {
				if (*(nums + i) > counter) {
					return counter;
				}
				/*��� ���� arr[i] < counter,
				��ʾ arr[i] �� arr[i-1] �����ظ���
				��ʱ���Ǳ���counter ���䣬i ���� */
			}
		}
		/* ���ѭ����������û�з��أ�
		˵��arr[begin] ~ arr[size-1] Ϊ������������
		��ʱ���� arr[size-1] + 1 */
		return *(nums + numsSize - 1) + 1;
	}
}

/**
* ���� n ������˵��������Ǵ� 1~ n �ģ�˵������ȱʧ�������������һ����
* ������ n, ˵������ 1~n ֮�ڣ��϶���ȱʧ�������������е� max ���ֵΪ n
*/
int firstMissingPositive2(int* nums, int numsSize) {
	int max = INT_MIN;
	for (int i = 0; i < numsSize; i++) {
		if (*(nums + i) > max) {
			max = *(nums + i);
		}
	}

	// ������ֵ���� n,���� 1 ~ n ֮��϶��м�ϵ㣬���ǲ���Ҫ��ȥ���Ǳ� n �����
	if (max > numsSize) {
		max = numsSize;
	}

	if (max < 1) { // ���е�������С�� 1��ֱ�ӷ���1
		return 1;
	}
	else {
		// ʹ��һ�����飬����� nums[i] - 1 ��ֵ 
		int* arr = (int*)malloc(sizeof(int) * max);
		for (int i = 0; i < max; i++) {
			*(arr + i) = 0;
		}
		for (int i = 0; i < numsSize; i++) {
			int value = *(nums + i);
			// ֻ���� 1~n ֮�����
			if (value >= 1 && value <= numsSize) {
				// ���ڳ��� nums[i]-1 �ı��Ϊ 1
				int index = value - 1;
				*(arr + index) = 1;
			}
		}
		for (int i = 0; i < max; i++) {
			// ��ʾ arr[j] - 1 = i ��û�г��֣��� i+1 ���ּ�ϵ�
			if (*(arr + i) == 0) {
				return i+1;
			}
		}
		// ����ֵ�����ڣ����� max + 1
		return max+1; 
	}
}

int main() {
	int nums[] = { 2147483647 };
	int size = sizeof(nums) / sizeof(int);
	int r = firstMissingPositive2(nums, size);
	printf("r is: %d\n", r);
	system("pause");
	return 0;
}