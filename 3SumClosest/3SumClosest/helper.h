#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

/**
* �������鲢����
* @param nums ԭ����ͷָ��
* @param size �����С
* @return ����������
*/
int* copyArray(int* nums, int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	int* p1 = nums;
	int* p2 = arr;
	while (p1 < nums + size) {
		*p2++ = *p1++;
	}
	return arr;
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
