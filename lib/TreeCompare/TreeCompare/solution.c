#include<stdlib.h>
#include<stdio.h>
#include "AVLTree.h"
#include "RBTree.h"
#include<time.h>

int* genArray(int size) {
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		*(arr + i) = i;
	}
	return arr;
}

long int getCurrentMills() {
	time_t t;
	time(&t);
	return t;
}


void test() {
	int size = 10000;
	int* datas = genArray(size);
	PAVLTree avl = NULL;
	PRBTree rb = newRBTree();
	printf("\n============== test insert %d nodes in rb tree ==============\n", size);
	long int b1 = getCurrentMills();
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		PRBTreeNode node = newRBTreeNode(key, rb->nil);
		RBInsert(rb, node);
	}
	long int e1 = getCurrentMills();
	printf("\n============== test insert %d nodes in avl tree ==============\n", size);
	long int b2 = getCurrentMills();
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		avl = AVLInsert(avl, key);
	}
	long int e2 = getCurrentMills();

	printf("insert rb tree took %d seconds, tree height is:%d\n", e1 - b1, getRBTreeHeight(rb, rb->root));
	printf("insert avl tree took %d seconds, tree height is:%d\n", e2 - b2,avl->treeHeight);

	printf("\n============== test delete %d nodes in rb tree ==============\n", size);
	long int b3 = getCurrentMills();
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		PRBTreeNode node = newRBTreeNode(key, rb->nil);
		RBRemove(rb, node);
	}
	long int e3 = getCurrentMills();

	printf("\n============== test delete %d nodes in avl tree ==============\n", size);
	long int b4 = getCurrentMills();
	for (int i = 0; i < size; i++) {
		int key = *(datas + i);
		avl = AVLDelete(avl, key);
	}
	long int e4 = getCurrentMills();
	
	printf("delete rb tree took %d seconds.\n", e3 - b3);
	printf("delete avl tree took %d seconds.\n", e4 - b4);

}

int main() {
	test();
	system("pause");
	return 0;
}