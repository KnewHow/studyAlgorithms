#include<stdio.h>
#include<stdlib.h>

void swap(int* arr, int index1, int index2) {
	int temp = *(arr + index1);
	*(arr + index1) = *(arr + index2);
	*(arr + index2) = temp;
}

void nextPermutation(int* nums, int numsSize) {
	if (numsSize > 1) {
		// �ҳ� nums �� nums[index] < nums[nextIndex]
		int index = -1;
		int nextIndex = -1;
		for (int i = 0; i < numsSize - 1; i++) {
			if (*(nums + i) < *(nums + i + 1)) {
				index = i;
				nextIndex = i + 1;
			}
		}
		// ���ҵ� index �ȽϿ���ķ���ʱ�����ǲ���ȷ��Ҫ���� indexNext ˳��
		// ���ǻ���Ҫ�Ƚ� indexNext �����Ƿ��� �� index ���ұ� indexNext ��С������ȵ���
		// ��ʾ����һ������
		if (index != -1 && nextIndex != -1) {
			int i = nextIndex + 1;
			int min = *(nums + nextIndex);
			while (i < numsSize) {
				if (*(nums + index) < *(nums + i) && *(nums + i) <= min) {
					min = *(nums + i);
					nextIndex = i;
				}
				i++;
			}
			swap(nums, index, nextIndex);
			// �ڽ���λ�ú���Ҫ�� index+1 ~ size ��Ԫ�ط�ת
			int mid = (index + 1 + numsSize) / 2;
			for (int j = index+1; j < mid; j++) {
				swap(nums, j, numsSize -j + index);
			}
		}
		else { // �����ʾ nums ��Ϊȫ�����������У�ֱ�ӷ�ת
			int mid = numsSize / 2;
			for (int i = 0; i < mid; i++) {
				swap(nums, i, numsSize - 1 - i);
			}
		}
	}
}

printfArray(int* arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			printf("%d", *(arr + i));
		}
		else {
			printf("%d,", *(arr + i));
		}
	}
	printf(" ]\n");
}

int main() {
	int nums[] = { 2,3,1,3,3 };
	int size = sizeof(nums) / sizeof(int);
	nextPermutation(nums, size);
	printfArray(nums, size);
	system("pause");
	return 0;
}