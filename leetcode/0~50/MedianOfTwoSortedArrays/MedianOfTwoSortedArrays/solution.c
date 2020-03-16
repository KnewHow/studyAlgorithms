#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

double findMedianSortedArraysWithMerge(
	int* nums1, 
	int nums1Size, 
	int* nums2, 
	int nums2Size) {
	int total = nums1Size + nums2Size;
	// �����ڴ棬��źϲ����������
	int* arr = (int*)(malloc(total * sizeof(int)));
	int i = 0;
	int j = 0;
	int index = 0;
	// �ϲ�����
	while (i < nums1Size || j < nums2Size) {
		if (i < nums1Size && j < nums2Size) {
			if (nums1[i] < nums2[j]) {
				arr[index] = nums1[i];
				i++;
			}
			else {
				arr[index] = nums2[j];
				j++;
			}
		}
		else if (i < nums1Size) {
			arr[index] = nums1[i];
			i++;
		}
		else {
			arr[index] = nums2[j];
			j++;
		}
		index++;
	}
	// ������Ԫ�ظ��������ż����ȡ��λ��
	if (total % 2 == 0) {
		int mid1 = total / 2 - 1;
		int mid2 = total / 2;
		return (arr[mid1] + arr[mid2]) / 2.0;
	}
	else {
		int mid = total / 2;
		return arr[mid] * 1.0;
	}
}

int getMin(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

/** ��ȡ�������������е� k С����
* @param b1 ��һ�������������ʼԪ�ص�ַ
* @param e1 ��һ�������������ֹԪ�ص�ַ
* @param b2 �ڶ��������������ʼԪ�ص�ַ
* @param e2 �ڶ��������������ֹԪ�ص�ַ
* ������Ϊ�գ��뽫 b �� e ����Ϊ NULL
* @param kths �� k С����,k �� 1 ��ʼ
* @return ���ص� k С����
*/
int getKthMin(
	int* b1,
	int* e1,
	int* b2,
	int* e2,
	int kths) {
	// kths Ϊ 1����ʾ����С��Ԫ�أ�ֱ���� b1 �� b2 ������С��Ԫ�ؼ���
	if (kths == 1) {
		if (b1 != NULL && b2 != NULL) {
			return getMin(*b1, *b2);
		}
		else if (b1 == NULL) {
			return *b2;
		}
		else {
			return *b1;
		}
	}
	else {
		if (b1 != NULL && b2 != NULL) {
			int mid = kths / 2 - 1;
			int midV1 = 0;
			int midV2 = 0;
			// ��� mid �Ѿ�Խ�磬ֱ���� e1 ��ֵ
			if (b1 + mid > e1) {
				midV1 = *e1;
			}
			else {
				midV1 = *(b1 + mid);
			}

			// get b mid value
			if (b2 + mid > e2) {
				midV2 = *e2;
			}
			else {
				midV2 = *(b2 + mid);
			}

			if (midV1 >= midV2) {
				// �� b2 ~ mid ��ȡ
				int *newB2 = NULL;
				int discardNumber = mid + 1;
				if (e2 - b2 < mid + 1) { // ��� mid Խ�磬ֱ�ӽ� b2 ��Ϊ NULL
					newB2 = NULL;
					discardNumber = (e2 - b2) + 1;
				}
				else {
					newB2 = b2 + mid + 1;
				}
				return getKthMin(b1, e1, newB2, e2, kths - discardNumber);
			}
			else {
				// �� b1 ~ mid ��ȡ
				int *newB1 = NULL;
				int discardNumber = mid + 1;
				if (e1 - b1 < mid + 1) { // ��� b1 Խ�磬ֱ�ӽ� b1 ��Ϊ NULL
					newB1 = NULL;
					discardNumber = (e1 - b1) + 1;
				}
				else {
					newB1 = b1 + mid + 1;
				}
				return getKthMin(newB1, e1, b2, e2, kths - discardNumber);
			}
		}
		else if (b1 == NULL) {
			return *(b2 + kths - 1);
		}
		else {
			return *(b1 + kths - 1);
		}
	}

}

// ���Ի�ȡ�� k СԪ�ص�ֵ
void getKthMinSpec() {
	int arr1[] = { 1,3,4,9 };
	int arr2[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr1Size = (sizeof(arr1) / sizeof(int));
	int arr2Size = (sizeof(arr2) / sizeof(int));
	int kths = 7;
	int r = getKthMin(arr1, arr1 + arr1Size - 1, arr2, arr2 + arr2Size - 1, kths);
	printf("%d ths is %d", kths, r);
}


double findMedianSortedArraysWithKthMin(
	int* nums1,
	int nums1Size,
	int* nums2,
	int nums2Size) {
	int* b1 = NULL;
	int* e1 = NULL;
	int* b2 = NULL;
	int* e2 = NULL;
	// ����Ԫ�طǿյ�����ָ�븳ֵ���������� begin �� end ��Ϊ NULL
	if (nums1Size > 0) {
		b1 = nums1;
		e1 = nums1 + nums1Size - 1;
	}
	if (nums2Size > 0) {
		b2 = nums2;
		e2 = nums2 + nums2Size - 1;
	}
	int total = (nums1Size + nums2Size);
	if (total % 2 == 0) {
		int mid1 = total / 2;
		int mid2 = total / 2 + 1;
		int r1 = getKthMin(b1, e1, b2, e2, mid1);
		int r2 = getKthMin(b1, e1, b2, e2, mid2);
		return (r1 + r2) / 2.0;
	}
	else {
		int mid = total / 2 + 1;
		int r = getKthMin(b1, e1, b2, e2, mid);
		return r * 1.0;
	}
}




int main() {
	int nums1[] = {3,4};
	int *nums2 = NULL;
	int nums1Size = sizeof(nums1) / sizeof(int);
	//int nums2Size = sizeof(nums2) / sizeof(int);
	double r = findMedianSortedArraysWithKthMin(nums1, nums1Size, nums2, 0);
	printf("media=%f\n", r);
	// getKthMinSpec();
	system("pause");
	return 0;
}