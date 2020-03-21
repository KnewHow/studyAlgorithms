#include<stdio.h>
#include<stdlib.h>
#include"hashMap.h"

int* genArray(int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(arr + i) = i;
	}
	return arr;
}

void testHashMap() {
	int size = 10240000;
	int *datas = genArray(size);
	PHashMap map = newHashMap();
	for (int i = 0; i < size - 1; i++) {
		int key = *(datas + i);
		int value = *(datas + i);
		hashTablePut(map, key, value);
	}
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		int r = hashTableContains(map, key);
		if (r == 0) {
			printf("map not contains key: %d\n", key);
		}
	}
	//for (int i = 0; i < size; i++) {
	//	int key = *(datas + i);
	//	// printf("remove key: %d\n", key);
	//	hashTableRemove(map, key);
	//}
	//for (int i = 0; i < size; i++) {
	//	int key = *(datas + i);
	//	int r = hashTableContains(map, key);
	//	// printf("map is contains key:%d, %d\n", key, r);
	//}
	destoryHashMap(map);
}

int main() {
	testHashMap();
	system("pause");
	return 0;
}