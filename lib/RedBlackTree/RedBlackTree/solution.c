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
	int size = 10000;
	int* arr = genArray(size);
	PRBTree tree = newRBTree();
	printf("============== test insert %d nodes in rb tree ==============\n\n", size);
	for (int i = 0; i < size; i++) {
		int key = *(arr + i);
		PRBTreeNode node = newRBTreeNode(key, tree->nil);
		RBInsert(tree, node);
		//printf("insert key: %d", key);
		/*int r1 = valid(tree);
		if (r1 == 0) {
			printf("valid failure");
			return;
		}*/
		//printf("\n");
	
		// levelTraverse(tree);
	}
	//levelTraverse(tree);
	 // int r = valid(tree);
	 // printf("valid result:%d\n", r);
	 printf("\n\ntree height is: %d\n", getRBTreeHeight(tree, tree->root));
	//printf("============== test delete %d nodes in rb tree ==============\n\n", size);
	//for (int i = 0; i < size; i++) {
	//	int key = *(arr + i);
	//	PRBTreeNode node = RBGetByKey(tree, tree->root, key);
	//	RBRemove(tree, node);
	//	printf("delete key: %d", key);
	//	//levelTraverse(tree);
	//	/*int r1 = valid(tree);
	//	if (r1 == 0) {
	//		printf("valid failure");
	//		return;
	//	}*/
	//	printf("\n");
	//}
	printf("============== destory RB tree ==============\n\n");
	destoryRBTree(tree);
	printf("============== test complete ==============\n\n");
	
	
}

int main() {
	RBTreeTest();
	system("pause");
	return 0;
}