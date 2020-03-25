#include<stdlib.h>
#include<stdio.h>

struct ListNode {
	int val;
	struct ListNode* next;
};



struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	while (1) {
		// ��ǰ����ͷ����СԪ�صĽǱ꣬��ʼ��Ϊ -1
		int minIndex = -1;
		for (int i = 0; i < listsSize; i++) {
			if (*(lists + i) != NULL) {
				if (minIndex == -1) { // δ��ʼ��
					minIndex = i;
				}
				else { // Ϊ��ʼ�������Ƚ�
					if ((*(lists + i))->val < (*(lists + minIndex))->val) {
						minIndex = i;
					}
				}
			}
		}
		if (minIndex == -1) { // ��ʾȫ��Ϊ NULL,����ѭ��
			break;
		}
		else {
			if (head == NULL) {
				head = *(lists + minIndex);
				tail = head;
				*(lists + minIndex) = (*(lists + minIndex))->next;
			}
			else {
				tail->next = *(lists + minIndex);
				tail = *(lists + minIndex);
				*(lists + minIndex) = (*(lists + minIndex))->next;
			}
		}
	}
	return head;
}

struct ListNode* arrayToList(int* arr, int size) {
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->next = NULL;
			head->val = *(arr + i);
			tail = head;
		}
		else {
			struct ListNode* e = (struct ListNode*)malloc(sizeof(struct ListNode));
			e->next = NULL;
			e->val = *(arr + i);
			tail->next = e;
			tail = e;
		}
	}
	return head;
}

void printList(struct ListNode* list) {
	while (list != NULL) {
		printf("%d->", list->val);
		list = list->next;
	}
	printf("end\n");
}

void quickSortR(int* arr, int begin, int end) {
	if (end - begin > 0) {
		int left = begin;
		int right = end;
		int pivot = *(arr + left);
		while (left < right) {
			while (left < right && *(arr + right) >= pivot) {
				right--;
			}
			while (left < right && *(arr + left) <= pivot) {
				left++;
			}

			int temp = *(arr + left);
			*(arr + left) = *(arr + right);
			*(arr + right) = temp;
		}
		int temp = *(arr + left);
		*(arr + left) = *(arr + begin);
		*(arr + begin) = temp;
		quickSortR(arr, begin, left - 1);
		quickSortR(arr, left + 1, end);
	}
}

void quickSort(int* arr, int size) {
	quickSortR(arr, 0, size - 1);
}

// �ֽ�����ת��Ϊ���飬Ȼ�������ڽ���������ת��Ϊ����
struct ListNode* mergeKLists2(struct ListNode** lists, int listsSize) {
	int* arr = (int*)malloc(sizeof(int) * 102400);
	int size = 0;
	// �������Ԫ�������������
	for (int i = 0; i < listsSize; i++) {
		struct ListNode* p = *(lists + i);
		while (p != NULL) {
			*(arr + size) = p->val;
			size++;
			p = p->next;
		}
	}
	// ��������п�������
	quickSort(arr, size);
	struct ListNode* head = NULL;
	struct ListNode* tail = head;
	// ��������Ԫ������µ�����
	for (int i = 0; i < size; i++) {
		if (head == NULL) {
			head = (struct ListNode*)malloc(sizeof(struct ListNode));
			head->val = *(arr + i);
			head->next = NULL;
			tail = head;
		}
		else {
			struct ListNode* e = (struct ListNode*)malloc(sizeof(struct ListNode));
			e->val = *(arr + i);
			e->next = NULL;
			tail->next = e;
			tail = e;
		}
	}
	return head;
}

int main() {
	int arr1[] = { 1,4,5 };
	int size1 = sizeof(arr1) / sizeof(int);
	int arr2[] = { 1,3,4 };
	int size2 = sizeof(arr2) / sizeof(int);
	int arr3[] = { 2,6 };
	int size3 = sizeof(arr3) / sizeof(int);
	struct ListNode* l1 = arrayToList(arr1, size1);
	struct ListNode* l2 = arrayToList(arr2, size2);
	struct ListNode* l3 = arrayToList(arr3, size3);
	struct ListNode** lists = (struct ListNode**)malloc(3 * sizeof(struct ListNode*));
	*(lists + 0) = l1;
	*(lists + 1) = l2;
	*(lists + 2) = l3;
	struct ListNode* r = mergeKLists2(lists, 3);
	printList(r);
	system("pause");
	return 0;
}