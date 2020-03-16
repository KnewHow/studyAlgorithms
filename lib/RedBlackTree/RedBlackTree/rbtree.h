#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define BLACK 0
#define RED 1


// ������Ľڵ㶨��
typedef struct RBTreeNode {
	int key; // Ԫ�ص�ֵ
	int color; // �ڵ����ɫ 0-��ɫ 1-��ɫ
	struct RBTreeNode* parent; // ���ڵ�ָ��
	struct RBTreeNode* left; // ������ָ��
	struct RBTreeNode* right; // ������ָ��
}RBTreeNode, *PRBTreeNode;

// �������������
typedef struct RBTree {
	PRBTreeNode root; // ���ڵ�
	PRBTreeNode nil; // �ڱ��ڵ� nil,��ʾ���пյ��ӽڵ�
	int height; // ����
}RBTree, *PRBTree;

// ��ʼ��һ�ú���������ڵ�Ϊ NULL
PRBTree newRBTree() {
	PRBTree tree = (PRBTree)malloc(sizeof(RBTree));
	PRBTreeNode nil = (PRBTreeNode)malloc(sizeof(RBTreeNode));
	// nil ����ɫΪ��ɫ�����඼����ν
	nil->key = 0;
	nil->color = BLACK;
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	tree->root = nil;
	tree->nil = nil;
	tree->height = 0;
	return tree;
}

PRBTreeNode newRBTreeNode(int key, PRBTreeNode nil) {
	PRBTreeNode node = (PRBTreeNode)malloc(sizeof(RBTreeNode));
	node->key = key;
	node->color = RED;
	node->left = nil;
	node->right = nil;
	node->parent = nil;
	return node;
}

/**
* ������ĸ߶�
*/
int getHeight(PRBTree tree, PRBTreeNode root) {
	if (root == tree->nil) {
		return 0;
	}
	else {
		int lh = getHeight(tree, root->left);
		int rh = getHeight(tree, root->right);
		return max(lh, rh) + 1;
	}
}

/**
* �Ժ���� tree �е� x ���� left ��ת
*/
void leftRotate(PRBTree tree, PRBTreeNode x) {
	PRBTreeNode y = x->right;
	x->right = y->left;
	if (y->left != tree->nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == tree->nil) {
		tree->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

/**
* �Ժ���� tree �е� y ���� right ��ת
*/
void rightRotate(PRBTree tree, PRBTreeNode y) {
	PRBTreeNode x = y->left;
	y->left = x->right;
	if (x->right != tree->nil) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == tree->nil) {
		x = tree->root;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}

/**
* �� z �ڵ���в����޸�
*/
void RBInsertFixup(PRBTree tree, PRBTreeNode z) {
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			PRBTreeNode y = z->parent->parent->right;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->right) {
				z = z->parent;
				leftRotate(tree, z);
			}
			if (z->parent != tree->nil) {
				z->parent->color = BLACK;
			}
			if (z->parent->parent != tree->nil) {
				z->parent->parent->color = RED;
				rightRotate(tree, z->parent->parent);
			}
		}
		else {
			PRBTreeNode y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else if (z == z->parent->left) {
				z = z->parent;
				rightRotate(tree, z);
			}
			if (z->parent != tree->nil) {
				z->parent->color = BLACK;
			}
			if (z->parent->parent != tree->nil) {
				z->parent->parent->color = RED;
				leftRotate(tree, z->parent->parent);
			}
			
		}
	}
	tree->root->color = BLACK;
}

void RBInsert(PRBTree tree, PRBTreeNode z) {
	PRBTreeNode y = tree->nil;
	PRBTreeNode x = tree->root;
	while (x != tree->nil) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (y == tree->nil) {
		tree->root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	z->left = tree->nil;
	z->right = tree->nil;
	z->color = RED;
	RBInsertFixup(tree, z);
	// ���¼�������
	tree->height = getHeight(tree, tree->root);
}

/**
* ��������������
*/
void RBTreeMiddleTraverse(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		RBTreeMiddleTraverse(tree, root->left);
		if (root->color == RED) {
			printf("�� ");
		}
		else {
			printf("�� ");
		}
		printf("%d ", root->key);
		RBTreeMiddleTraverse(tree, root->right);
	}
}

/**
* ��ӡָ����������
* @param root ���ڵ�
* @param currentLevel ��ǰ��
* @param level ��Ҫ��ӡ�Ĳ����ڵ�
*/
void printLevel(PRBTree tree, PRBTreeNode root, int currentLevel, int level, int space) {
	if (root != tree->nil) {
		if (currentLevel == level) { // �����Ӧ�Ĳ���
			if (root->color == RED) {
				printf("r");
			}
			else {
				printf("b");
			}
			printf("%d", root->key);
			for (int i = 0; i < space; i++) {
				printf(" ");
			}
		}
		else { // ��û��,����������
			printLevel(tree, root->left, currentLevel + 1, level, space);
			printLevel(tree, root->right, currentLevel + 1, level, space);
		}
	}
	else {
		printf("b-");
		for (int i = 0; i < space; i++) {
			printf(" ");
		}
	}
}

/**
* �����������ֱ�۵Ŀ���������״
*/
void levelTraverse(PRBTree tree) {
	int height = tree->height;
	for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < pow(2, height - i); j++) {
			printf(" ");
		}
		printLevel(tree, tree->root, 0, i, pow(2, height-i));
		printf("\n");
	}
}


/**
* У�����1��3��
* 1.���ں������˵��ÿ���ڵ㣬Ҫô�Ǻ�ɫ��Ҫô�Ǻ�ɫ
* 3. Ҷ�ڵ� nil �Ǻ�ɫ��
*/
int validRule1And3(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		int r = 0;
		if (root->color == RED || root->color == BLACK) {
			r = 1;
		}
		else {
			printf("node key is: %d, valid rule 1 failure\n", root->key);
		}
		int rLeft = validRule1And3(tree, root->left);
		int rRight = validRule1And3(tree, root->right);
		return r && rLeft && rRight;
	}
	else {
		if (root->color == BLACK) {
			return 1;
		}
		else {
			printf("leaf node nil is not black\n");
			return 0;
		}
	}
}

/**
* У�����4�����һ���ڵ��Ǻ�ɫ�ģ���ô���������ֵ㶼�Ǻ�ɫ��
*/
int validRule4(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		if (root->color == BLACK) {
			return validRule4(tree, root->left) && validRule4(tree, root->right);
		}
		else {
			int r = 0;
			if (root->left->color == BLACK && root->right->color == BLACK) {
				r = 1;
			}
			r && validRule4(tree, root->left) && validRule4(tree, root->right);
		}
	}
	else { // nil ����ҪУ�飬ֱ�ӷ��سɹ�
		return 1;
	}
}

/**
* У����� 5����ÿ���ڵ㣬�������к����Ҷ�ڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
* @return �ýڵ㵽���������ĺ�ɫ�ڵ���
*/
int validRule5(PRBTree tree, PRBTreeNode root, int *returnR5) {
	if (root != tree->nil) {
		int lb = validRule5(tree, root->left, returnR5);
		int rb = validRule5(tree, root->right, returnR5);
		// У��ʧ��
		if (lb != rb) {
			printf("root node key: %d left blacks: %d, and rigth black :%d not equal\n", root->key, lb, rb);
			*returnR5 = 0;
			// ��������Ѿ���ʵ�Ѿ�����ν��
			return lb;
		}
		else {
			if (root->color == BLACK) { // ����ýڵ㱾���Ǻ�ɫ�ڵ� +1������ֻ���������ĺ�ɫ�ڵ���
				return 1 + lb;
			}
			else {
				return lb;
			}
		}
		
	}
	else { // nil ��һ���ڽڵ�
		return 1;
	}
}

/**
* У��һ�ú�����Ƿ�������º�����Ĺ���
* 1. ÿ���ڵ㣬Ҫô�Ǻ�ɫ��Ҫô�Ǻ�ɫ
* 2. ���ڵ��Ǻ�ɫ��
* 3. ÿ��Ҷ�ڵ� nil �Ǻ�ɫ��
* 4. ���һ���ڵ��Ǻ�ɫ�ģ���ô���������ֵ㶼�Ǻ�ɫ��
* 5. ��ÿ���ڵ㣬�������к����Ҷ�ڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
*/
int valid(PRBTree tree) {
	int r13 = validRule1And3(tree, tree->root);
	int r2 = 0;
	if (tree->root->color == BLACK) {
		r2 = 1;
	}
	else {
		printf("root node is not black\n");
		r2 = 0;
	}
	int r4 = validRule4(tree, tree->root);
	int r5 = 1;
	validRule5(tree, tree->root, &r5);
	return r13 && r2 && r4 & r5;;
}

