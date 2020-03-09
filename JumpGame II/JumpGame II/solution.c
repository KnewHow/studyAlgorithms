#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/**
* ���ص�ǰ�㵽�յ����С����
* @param nums ԭ����
* @param numsSize ԭ�����С
* @param position ��ǰλ��
* @param steps ��ǰ�Ѿ����˶��ٲ�
* @param minSteps ��ԭ���������Ӧ����Ӧÿ��λ�õ��յ����С������Ϊ���Ż��ݹ���ظ�����
* @returnMinStep ����㵽�յ����С������ָ��
* @return �ӵ�ǰλ�õ��յ����С����
*/
int go(int *nums, int numsSize, int position, int steps,  int *minSteps) {
	// �����յ�
	if (position == numsSize - 1) {
		return 0;
	}
	else { // ��û��
		// ֮ǰ�Ѿ������
		if (*(minSteps + position) != 0) {
			return *(minSteps + position);
		}
		else {
			int range = *(nums + position);
			int min = INT_MAX;
			for (int j = 1; j <= range; j++) {
				if (position + j <= numsSize - 1) {
					int r = go(nums, numsSize, position + j, steps + 1, minSteps);
					// ������� INT_MAX  ˵����·��ͨ
					if (r == INT_MAX) {
						continue;
					}
					if (r + 1 < min) {
						min = r + 1;
					}
				}
			}
			*(minSteps + position) = min;
			return min;
		}
	}
}

int jump(int* nums, int numsSize) {
	// һ�����飬�洢��ǰλ�õ��յ����С���룬��ʼ��Ϊ0��ÿ�εݹ�����
	int* minSteps = (int*)malloc(sizeof(int) * numsSize);
	for (int i = 0; i < numsSize; i++) {
		*(minSteps + i) = 0;
	}
	int r = go(nums, numsSize, 0, 0, minSteps);
	free(minSteps);
	return r;
}

/**
* ˳������(̰���㷨)
*/
int jump2(int* nums, int numsSize) {
	int steps = 0;
	int end = 0;
	int maxPosition = 0;
	// ��Ϊ�յ��� numsSize-1,�Լ������Լ�������Ҫ0�������Բ���Ҫ����
	for (int i = 0; i < numsSize - 1; i++) {
		// ÿ�μ�¼�ӵ�ǰλ�ÿ�����Ծ����Զλ�ã�����¼����
		maxPosition = max(maxPosition, nums[i] + i);
		/**
		* ��ʼ��������� end = 0 ʱ���������Ϊ����Ҫ������һ��
		* ���� end == i ʱ�򣬱�ʾҪ���ﵱǰ�� maxPosition,��Ҫ��ԭ���Ļ����ϣ�����һ����
		*/
		if (end == i) {
			end = maxPosition;
			steps++;
		}
	}
	return steps;
}

int main() {
	int nums[] = { 2,3,1,1,4 };
	int size = sizeof(nums) / sizeof(int);
	int r = jump2(nums, size);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}