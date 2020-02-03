#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include"helper.h"
#include<Windows.h>

/*AVL 树相关的操作*/
typedef struct Node
{
	int value;
	struct Node* left;
	struct Node* right;
	int height;
} Tree, *PTree;

// 根据值去查找节点
PTree find(PTree root, int target) {
	if (root == NULL) {
		return NULL;
	}else {
		PTree temp = root;
		while (temp != NULL) {
			if (temp->value == target) {
				return temp;
			}
			else if (target > temp->value) {
				temp = temp->right;
			}
			else {
				temp = temp->left;
			}
		}
		return NULL;
	}
}

int getMax(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int getHeight(PTree root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return getMax(getHeight(root->left),getHeight(root->right)) + 1;
	}
}

// LL 调整
PTree LL(PTree root) {
	PTree b = root->left;
	root->left = b->right;
	b->right = root;
	root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
	b->height = getMax(getHeight(b->left), getHeight(b->right)) + 1;
	return b;
}

// RR 调整
PTree RR(PTree root) {
	PTree b = root->right;
	root->right = b->left;
	b->left = root;
	root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
	b->height = getMax(getHeight(b->left), getHeight(b->right)) + 1;
	return b;
}

// LR 调整
PTree LR(PTree root) {
	PTree b = RR(root->left);
	root->left = b;
	return LL(root);
}

// RL 调整
PTree RL(PTree root) {
	PTree b = LL(root->right);
	root->right = b;
	return RR(root);
}

// 添加一个元素
PTree push(PTree root, int value) {
	if (root == NULL) {
		root = (PTree)malloc(sizeof(Tree));
		if (root != NULL) {
			root->value = value;
			root->left = NULL;
			root->right = NULL;
			root->height = 0;
		} else {
			printf("[avl tree-push] malloc apply memory failure\n");
			return NULL;
		}
	} else {
		if (value <= root->value) {
			root->left = push(root->left, value);
			// 出现不平衡
			if (getHeight(root->left) - getHeight(root->right) >= 2) {
				if (value <= root->left->value) {
					root = LL(root);
				}
				else {
					root = LR(root);
				}
			}
		}
		else {
			root->right = push(root->right, value);
			// 出现不平衡
			if (getHeight(root->right) - getHeight(root->left) >= 2) {
				if (value <= root->right->value) {
					root = RL(root);
				}
				else {
					root = RR(root);
				}
			}
		}
	}
	root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
	return root;
}

// 先序遍历
void preOrderPrint(PTree root) {
	if (root != NULL) {
		printf("%d ", root->value);
		preOrderPrint(root->left);
		preOrderPrint(root->right);
	}
}

// 测试 AVL 树的生成
void testAVLTreeGen() {
	int arr[] = { 30,15,41,33,50,35 };
	PTree root = NULL;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		root = push(root, arr[i]);
	}
	preOrderPrint(root);
}

void testPerformance() {
	int n = 100000;
	PTree root = NULL;
	long int s1 = getCurrentMills();
	for (int i = 0; i < n; i++) {
		DWORD  a1 = GetTickCount64();
		root = push(root, i);
		DWORD a2 = GetTickCount64();
		printf("push [%d] took %d\n", i, (a2 - a1));
	}
	long int s2 = getCurrentMills();
	for (int i = 0; i < n; i++) {
		find(root, i);
	}
	long int s3 = getCurrentMills();
	printf("insert took time=%ld\n", s2 - s1);
	printf("find all took time=%ld\n", s3 - s2);
}



