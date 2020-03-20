#include<stdio.h>
#include<stdlib.h>
#include "avltree.h"

int* genArray(int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(arr + i) = i;
	}
	return arr;
}

void testAVLTree() {
	int size = 10000;
	int* datas = genArray(size);
	PAVLTree tree = NULL;
	printf("\n==========test insert avl tree==========\n");
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		tree = AVLInsert(tree, key);
		// printf("insert key is: %d, avl tree height is: %d\n", key, tree->treeHeight);
	}
	printf("\n==========test delete avl tree==========\n");

	for (int i = 0; i < size - 1; i++) {
		int key = *(datas + i);
		tree = AVLDelete(tree, key);
		// printf("delete key is: %d, avl tree height is: %d\n", key, tree->treeHeight);
	}
	printf("\n==========test avl tree complete ==========\n");

}

int main() {
	testAVLTree();
	system("pause");
	return 0;
}