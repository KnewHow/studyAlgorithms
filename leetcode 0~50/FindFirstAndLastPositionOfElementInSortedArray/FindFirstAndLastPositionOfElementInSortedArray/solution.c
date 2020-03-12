#include<stdlib.h>
#include<stdio.h>


/**
* �� mid ��λ����ǰ�ң��ҵ� target ��һ�γ��ֵ�λ�ü�����ʹ�õ���ÿ�η�����˼�룬
* �� 2^n ���ٶȱƽ�
* @param nums ԭ�������������
* @param numsSize �����С
* @param target Ŀ����
* @param mid Ŀ�������ڵ�һ���Ǳ�
* @param ���� target ������ nums ���״γ��ֵĽǱ�
*/
int findFirstPositionDecrease(
	int* nums, 
	int numsSize, 
	int target, 
	int mid
) {
	// ÿ�δ� 1 ��ʼ����
	int tb = 1;
	int counter = 1;
	if (mid - tb < 0) {
		return 0;
	}
	if (*(nums + mid - tb) != target) {
		return 0;
	}
	while (mid - 2 * tb >= 0 && *(nums + mid - 2 * tb) == target) {
		tb += tb;
		counter += counter;
	}
	return counter + findFirstPositionDecrease(nums, numsSize, target, mid - counter);
}

/**
 �� mid ��λ�������ң��ҵ� target ���һ�γ��ֵ�λ������
*/
int findLastPositionIncrease(
	int* nums,
	int numsSize,
	int target,
	int mid) {
	int tb = 1;
	if (mid + tb >= numsSize) {
		return 0;
	}
	if (*(nums + mid + tb) != target) {
		return 0;
	}
	int counter = 1;
	while (mid + 2 * tb < numsSize && *(nums + mid + 2 * tb) == target) {
		counter += counter;
		tb += tb;
	}
	return counter + findLastPositionIncrease(nums, numsSize, target, mid + counter);
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	*returnSize = 2;
	int* r = (int*)malloc(sizeof(int) * 2);
	int begin = 0;
	int end = numsSize - 1;
	while (begin <= end) {
		int mid = (begin + end) / 2;
		if (target  == *(nums + mid)) {
			int firstDecrease = findFirstPositionDecrease(nums, numsSize, target, mid);
			int lastIncrease = findLastPositionIncrease(nums, numsSize, target, mid);
			*(r + 0) = mid - firstDecrease;
			*(r + 1) = mid + lastIncrease;
			return r;
		}
		else if (target < *(nums + mid)) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	// û���ҵ�
	*(r + 0) = -1;
	*(r + 1) = -1;
	return r;
}

void printArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d, ", *(arr + i));
		}
	}
	printf(" ]\n");
}

int main() {
	int nums[] = { 1 };
	int size = sizeof(nums) / sizeof(int);
	int target = 1;
	int returnSize = 0;
	int* r = searchRange(nums, size, target, &returnSize);
	printArray(r, returnSize);
	system("pause");
	return 0;
}