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
}RBTree, *PRBTree;

// ��ź�����ڵ������
typedef struct RBTreeNodeList {
	PRBTreeNode node;
	struct RBTreeNodeList *next;
}RBTreeNodeList, *PRBTreeNodeList;

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
int getRBTreeHeight(PRBTree tree, PRBTreeNode root) {
	if (root == tree->nil) {
		return 0;
	}
	else {
		int lh = getRBTreeHeight(tree, root->left);
		int rh = getRBTreeHeight(tree, root->right);
		return max(lh, rh) + 1;
	}
}

PRBTreeNode RBMin(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		if (root->left != tree->nil) {
			RBMin(tree, root->left);
		}
		else {
			return root;
		}
	}
	else {
		return tree->nil;
	}
}

PRBTreeNode RBGetByKey(PRBTree tree, PRBTreeNode root, int key) {
	if (root == tree->nil) {
		return tree->nil; // not found
	}
	else if (root->key == key) {
		return root;
	}
	else if (root->key < key) {
		return RBGetByKey(tree, root->right, key);
	}
	else {
		return RBGetByKey(tree, root->left, key);
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
		tree->root = x;
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
				continue;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftRotate(tree, z);
					continue;
				}
				else {
					if (z->parent != tree->nil) {
						z->parent->color = BLACK;
					}
					if (z->parent->parent != tree->nil) {
						z->parent->parent->color = RED;
						rightRotate(tree, z->parent->parent);
					}
				}
			}
			
			
		}
		else {
			PRBTreeNode y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
				continue;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotate(tree, z);
					continue;
				}
				else {
					if (z->parent != tree->nil) {
						z->parent->color = BLACK;
					}
					if (z->parent->parent != tree->nil) {
						z->parent->parent->color = RED;
						leftRotate(tree, z->parent->parent);
					}
				}
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
}

/**
* �Խڵ� x ����ɾ���޸�
*/
void RBRemoveFixup(PRBTree tree, PRBTreeNode x) {
	while (x != tree->nil && x != tree->root && x->color == BLACK) {
		if (x == x->parent->left) {
			PRBTreeNode w = x->parent->right;
			if (w->color == RED && w != tree->nil) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(tree, x->parent);
				w = x->parent->right;
			}
			if (w == tree->nil
				|| (w!= tree->nil && (w->left == tree->nil || w->left->color == BLACK) 
					&& (w->right == tree->nil || w->right->color == BLACK))) {
				if (w != tree->nil) {
					w->color = RED;
				}
				x = x->parent;
				continue;
			}
			else if (w->right == tree->nil || w->right->color == BLACK) {
				w->left->color = BLACK;
				w->color = RED;
				rightRotate(tree, w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->right->color = BLACK;
			leftRotate(tree, x->parent);
			x = tree->root;
		}
		else {
			PRBTreeNode w = x->parent->left;
			if (w!= tree->nil && w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(tree, x->parent);
				w = x->parent->left;
			}
			if (w == tree->nil
				|| (w != tree->nil && (w->left == tree->nil || w->left->color == BLACK)
					&& (w->right == tree->nil || w->right->color == BLACK))) {
				if (w != tree->nil) {
					w->color = RED;
				}
				x = x->parent;
				continue;
			}
			else if (w->left == tree->nil || w->left->color == BLACK) {
				w->right->color = BLACK;
				w->color = RED;
				leftRotate(tree, w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left->color = BLACK;
			rightRotate(tree, x->parent);
			x = tree->root;
		}
	}
	x->color = BLACK;
}

void RBTransplant(PRBTree tree, PRBTreeNode u, PRBTreeNode v) {
	if (u->parent == tree->nil) {
		tree->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if (v != tree->nil) {
		v->parent = u->parent;
	}
}

void RBRemove(PRBTree tree, PRBTreeNode z) {
	PRBTreeNode y = z;
	PRBTreeNode x = tree->root;
	int yOriginalColor = y->color;
	if (z->left == tree->nil) {
		x = z->right;
		RBTransplant(tree, z, z->right);
	}
	else if (z->right == tree->nil) {
		x = z->left;
		RBTransplant(tree, z, z->left);
	}
	else {
		y = RBMin(tree, z->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->parent == z) {
			x->parent = y;
		}
		else {
			RBTransplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		RBTransplant(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (yOriginalColor == BLACK) {
		RBRemoveFixup(tree, x);
	}
	free(z);
}

void destoryRBTree(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		if (root->left == tree->nil && root->right == tree->nil) { // Ҷ�ӽڵ㣬 free
			if (root == root->parent->left) {
				root->parent->left = tree->nil;
			}
			else {
				root->parent->right = tree->nil;
			}
			free(root);
		}
		else { // ����Ҷ�ӽڵ�
			destoryRBTree(tree, root->left);
			destoryRBTree(tree, root->right);
			if (root->parent == tree->nil) { // root Ϊ���ڵ�
				free(root);
				free(tree->nil);
				free(tree);
			}
			else { // root ���Ǹ��ڵ㣬free root��Ȼ�󽫽ڵ�ָ�� root ��������Ϊ nil
				if (root == root->parent->left) {
					root->parent->left = tree->nil;
				}
				else {
					root->parent->right = tree->nil;
				}
				free(root);
			}
		}
	}
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
				printf("R");
			}
			else {
				printf("B");
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
		printf("B-");
		for (int i = 0; i < space; i++) {
			printf(" ");
		}
	}
}

/**
* �����������ֱ�۵Ŀ���������״
*/
void levelTraverse(PRBTree tree) {
	int height = getRBTreeHeight(tree, tree->root);
	int d = 2;
	for (int i = 0; i < height; i++) {
		int step = pow(2, height - 1 - i) * 2;
		for (int j = 0; j < step; j++) {
			printf(" ");
		}
		int dis = pow(2, height - i) - 1;
		printLevel(tree, tree->root, 0, i,  dis* d);
		printf("\n\n");
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
			else {
				printf("node %d is red, but its left and right not all black\n", root->key);
			}
			return r && validRule4(tree, root->left) && validRule4(tree, root->right);
		}
	}
	else { // nil ����ҪУ�飬ֱ�ӷ��سɹ�
		return 1;
	}
}


/**
* �����������е�Ҷ�ӽڵ㣬���䱣���� list ��
*/
void getAllLeafNodesR(PRBTree tree, PRBTreeNode root, PRBTreeNodeList *list) {
	
	if (root != tree->nil) {
		// ���ڵ㲻Ϊ�գ�������������Ϊ��ʱ��ΪҶ�ڵ�
		if (root->left == tree->nil && root->right == tree->nil) {
			if (*list == NULL) {
				*list = (PRBTreeNodeList)malloc(sizeof(RBTreeNodeList));
				(*list)->node = root;
				(*list)->next = NULL;
			}
			else {
				PRBTreeNodeList newNode = (PRBTreeNodeList)malloc(sizeof(RBTreeNodeList));
				newNode->node = root;
				newNode->next = *list;
				*list = newNode;
			}
		}
		else {
			getAllLeafNodesR(tree, root->left, list);
			getAllLeafNodesR(tree, root->right, list);
		}
	}
}

/**
* ��ȡ��������е�Ҷ�ӽڵ㣬ʹ���������ʽ����
*/
PRBTreeNodeList getAllLeafNodes(PRBTree tree, PRBTreeNode root) {
	PRBTreeNodeList list = NULL;
	getAllLeafNodesR(tree, root, &list);
	return list;
}

/**
* �ӽڵ� root ���� �ڵ� target ��Ҫ�����ĺ�ɫ�ڵ���
* ����ӽڵ� root �޷�ͨ�������������������� target, ���� -1����ʾ���ɴ�
*/
int clcReachLeavesBlackNodes(PRBTree tree, PRBTreeNode root, PRBTreeNode target, int blackNodes) {
	if (root != tree->nil) {
		int currentBlackNodes = 0;
		if (root->color == BLACK) {
			currentBlackNodes = 1;
		}
		if (target->key < root->key) {
			return clcReachLeavesBlackNodes(tree, root->left, target, blackNodes + currentBlackNodes);
		}
		else if (target->key > root->key) {
			return clcReachLeavesBlackNodes(tree, root->right, target, blackNodes + currentBlackNodes);
		}
		else { // �ҵ���
			return  blackNodes + currentBlackNodes;
		}
	}
	else { // û�ҵ�
		return -1;
	}
}

/**
* У����ڵ㵽����Ҷ�ӽڵ㾭���ĺ�ɫ�ڵ������Ƚ��Ƿ���ȣ��������ȣ�����1�����򷵻�0
* ���ڲ��ɴ�Ľڵ㣬ʹ�� -1 ��ʾ������ҪУ��
*/
int validRootReachEachLeaves(PRBTree tree, PRBTreeNode root, PRBTreeNodeList leaves, int leavesSize) {
	int* res = (int*)malloc(sizeof(int) * leavesSize);
	PRBTreeNodeList p = leaves;
	int previous = -1;
	while (p != NULL) {
		int blackNodes = clcReachLeavesBlackNodes(tree, root, p->node, 0);
		if (blackNodes != -1) {
			if (previous == -1) { // ��һ�������ɴ��Ҷ�ӽڵ�
				previous = blackNodes;
			}
			else {
				if (blackNodes != previous) {
					printf("root key:%d reach leaf key:%d is not equal previous\n", root->key, p->node->key);
					return 0;
				}
			}
		}
		p = p->next;
	}
	return 1;
}

/**
* �����������еķ�Ҷ�ӽڵ㵽����Ҷ�ӽڵ�ļ�·���ĺ�ɫ���ڵ�����
*/
void validRule5R(PRBTree tree, PRBTreeNode root, PRBTreeNodeList leaves, int leavesSize, int* returnR5) {
	if (root != tree->nil) {
		int r = validRootReachEachLeaves(tree, root, leaves, leavesSize);
		if (r == 0) {
			*returnR5 = 0;
		}
		validRule5R(tree, root->left, leaves, leavesSize,returnR5);
		validRule5R(tree, root->right, leaves, leavesSize, returnR5);
	}
}

/**
* У����� 5����ÿ���ڵ㣬�������к����Ҷ�ڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
* @return �ýڵ㵽���������ĺ�ɫ�ڵ���
*/
int validRule5(PRBTree tree, PRBTreeNode root) {
	PRBTreeNodeList leaves = getAllLeafNodes(tree, root);
	PRBTreeNodeList p = leaves;
	int leavesSize = 0;
	while (p != NULL) {
		leavesSize++;
		p = p->next;
	}
	int returnR5 = 1;
	validRule5R(tree, root, leaves, leavesSize, &returnR5);
	p = leaves;
	while (p != NULL) {
		PRBTreeNodeList q = p;
		p = p->next;
		free(q);
	}
	return returnR5;
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
	int r5 = validRule5(tree, tree->root);
	return r13 && r2 && r4 & r5;;
}

