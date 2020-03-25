#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#define N 1024

typedef struct Element {
	int* tuple; // һά���飬
	int size; // �����С
	struct Element* next; // ָ���¸�Ԫ�ص�ָ��
} Element, *PElement;

typedef struct Number {
	int value; // ���ֵ�ֵ
	int index; // ������ԭ�����µĽǱ�
	struct Number* next;
} Number, *PNumber;

// HashTable
typedef struct HashTable {
	int size; // hash table �� size
	PElement* tables; // ����� hash Ͱ��ʵ���Ͼ��Ǹ�����
} HashTable, *PHashTable;

// ��ȡһ�����ľ���ֵ
int absV(int a) {
	if (a >= 0) {
		return a;
	}
	else {
		return -a;
	}
}

/**
* ����ÿ�� Element �� hashCode,����ʹ��������ÿ��Ԫ�صľ���ֵ���
* ��������������ֵ���������»ᵼ�� int �����
* ��������Ż�Ϊʹ��ÿ�������ַ��� ASCII ��ӣ�����������������
* @param nums ����
* @param size ���� size
* @return ������ hashCode
*/
int hashCode(int* nums, int size) {
	int* p = nums;
	int code = 0;
	while (p < nums + size) {
		code += absV(*p);
		p++;
	}
	return code;
}

PHashTable initHashTable() {
	PElement* tables = (PElement*)malloc(N * sizeof(PElement));
	PElement* p = tables;
	while (p < tables + N) {
		*p = NULL;
		p++;
	}
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	hashTable->size = 0;
	hashTable->tables = tables;
	return hashTable;
}

int isSame(PElement e, int* nums, int size) {
	int* p1 = e->tuple;
	int* p2 = nums;
	while (p1 < e->tuple + e->size && p2 < nums + size) {
		if (*p1 != *p2) {
			return 0;
		}
		p1++;
		p2++;
	}
	if (p1 == e->tuple + e->size && p2 == nums + size) { // ���������
		return 1;
	}
	else { // ��һ��δ�������
		return 0;
	}
}

int exists(PHashTable hashTable, int* nums, int size) {
	int code = hashCode(nums, size);
	int index = code % N;
	PElement head = *(hashTable->tables + index);
	if (head == NULL) {
		return 0;
	}
	else {
		PElement p = head;
		while (p != NULL) {
			if (isSame(p, nums, size)) { // �����ͬ��˵������
				return 1;
			}
			else { // ����Ƚ���һ��
				p = p->next;
			}
		}
		return 0; // ���궼û����ͬ���򲻰���
	}
}

void put(PHashTable hashTable, int* nums, int size) {
	int code = hashCode(nums, size);
	int index = code % N;
	PElement head = *(hashTable->tables + index);
	if (head == NULL) { // û��Ԫ��
		head = (PElement)malloc(sizeof(Element));
		head->size = size;
		head->tuple = nums;
		head->next = NULL;
		*(hashTable->tables + index) = head;
		hashTable->size++;
	}
	else {
		PElement e = (PElement)malloc(sizeof(Element));
		e->size = size;
		e->tuple = nums;
		e->next = head;
		*(hashTable->tables + index) = e;
		hashTable->size++;
	}
}



// �� hashTable ת��Ϊ��ά����
int** toArray(PHashTable hashTable) {
	int** arr = (int**)malloc(hashTable->size * sizeof(int*));
	int** p = arr;
	PElement* tables = hashTable->tables;
	for (int i = 0; i < N; i++) {
		PElement head = *(tables + i);
		if (head != NULL) {
			PElement q = head;
			while (q != NULL) {
				*p = q->tuple;
				p++;
				q = q->next;
			}
		}
	}
	return arr;
}

// �洢���ֺͽǱ�� hashTable,�����������
PNumber* initNumberHashTable() {
	PNumber* numbers = (PNumber*)malloc(sizeof(PNumber) * N);
	for (int i = 0; i < N; i++) {
		*(numbers + i) = NULL;
	}
	return numbers;
}

/**
* �� hashTable ����һ����
* @param numbers ��ϣ��
* @param value ���ֵ�ֵ
* @param index ������ԭ������±�
*/
void putNumber(PNumber* numbers, int value, int index) {
	int code = absV(value);
	int pos = code % N;
	PNumber head = *(numbers + pos);
	if (head == NULL) {
		head = (PNumber)malloc(sizeof(Number));
		head->index = index;
		head->value = value;
		head->next = NULL;
		*(numbers + pos) = head;
	}
	else {
		PNumber n = (PNumber)malloc(sizeof(Number));
		n->index = index;
		n->value = value;
		n->next = head;
		*(numbers + pos) = n;
	}
}

/**
* ��ȡֵΪvalue,���� index != index ��Ԫ��
* @params numbers �Ѿ���ʼ���� hash ��
* @params value ��Ҫ���ҵ���ֵ
* @params index ���ҵ�ֵ��Ҫ�����ڵ�ǰ�� index
* @params index2 ���Ҳ����� index2 �ĽǱ꣬���index ==-1,����
* @return ����ҵ�Ԫ�أ����ض�Ӧ�� PNumber���Ҳ������� NULL
*/
PNumber get(
	PNumber* numbers, 
	int value,
	int index,
	int index2
) {
	int code = absV(value);
	int pos = code % 1024;
	PNumber head = numbers[pos];
	if (head == NULL) {
		return NULL;
	}
	else {
		PNumber p = head;
		while (p != NULL) {
			if (index2 == -1) {
				if (p->value == value && p->index != index) {
					return p;
				}
			}
			else {
				if (p->value == value 
					&& p->index != index 
					&& p->index != index2) {
					return p;
				}
			}
			p = p->next;
		}
		return NULL;
	}
}
