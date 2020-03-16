#include<stdio.h>
#include<stdlib.h>
#include "rbtree.h"

int* genArray(int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(arr + i) = i;
	}
	return arr;
}

void RBTreeTest() {
	int size = 10;
	int* arr = genArray(size);
	PRBTree tree = newRBTree();
	for (int i = 0; i < size; i++) {
		int key = *(arr + i);
		PRBTreeNode node = newRBTreeNode(key, tree->nil);
		RBInsert(tree, node);
	}
	int r = valid(tree);
	levelTraverse(tree);
	printf("valid r is: %d\n", r);
	
}

int main() {
	RBTreeTest();
	system("pause");
	return 0;
}