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
	printf("test insert==============\n\n");
	for (int i = 0; i < size; i++) {
		int key = *(arr + i);
		PRBTreeNode node = newRBTreeNode(key, tree->nil);
		RBInsert(tree, node);
	}
	int r1 = valid(tree);
	printf("valid result:%d\n", r1);
	printf("tree height is: %d\n", getHeight(tree, tree->root));
	levelTraverse(tree);
	printf("test delete tree ==============\n\n");
	for (int i = 0; i < size; i++) {
		int key = *(arr + i);
		PRBTreeNode node = RBGetByKey(tree, tree->root, key);
		//RBRemove(tree, node);
		// int r = valid(tree);
		//printf("delete key: %d, valid r is: %d,height is: %d, \n\n", key, r, tree->height);
		// levelTraverse(tree);
	}
	
	
}

int main() {
	RBTreeTest();
	system("pause");
	return 0;
}