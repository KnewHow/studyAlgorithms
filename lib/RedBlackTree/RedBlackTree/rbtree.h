#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<math.h>
#define BLACK 0
#define RED 1


// 红黑树的节点定义
typedef struct RBTreeNode {
	int key; // 元素的值
	int color; // 节点的颜色 0-黑色 1-红色
	struct RBTreeNode* parent; // 父节点指针
	struct RBTreeNode* left; // 左子树指针
	struct RBTreeNode* right; // 右子树指针
}RBTreeNode, *PRBTreeNode;

// 红黑树构建定义
typedef struct RBTree {
	PRBTreeNode root; // 根节点
	PRBTreeNode nil; // 哨兵节点 nil,表示所有空的子节点
}RBTree, *PRBTree;

// 存放红黑树节点的链表
typedef struct RBTreeNodeList {
	PRBTreeNode node;
	struct RBTreeNodeList *next;
}RBTreeNodeList, *PRBTreeNodeList;

// 初始化一棵红黑树，根节点为 NULL
PRBTree newRBTree() {
	PRBTree tree = (PRBTree)malloc(sizeof(RBTree));
	PRBTreeNode nil = (PRBTreeNode)malloc(sizeof(RBTreeNode));
	// nil 的颜色为黑色，其余都无所谓
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
* 红黑树的高度
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
* 对红黑树 tree 中的 x 进行 left 旋转
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
* 对红黑树 tree 中的 y 进行 right 旋转
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
* 对 z 节点进行插入修复
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
	// 重新计算树高
}

/**
* 对节点 x 进行删除修复
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
		if (root->left == tree->nil && root->right == tree->nil) { // 叶子节点， free
			if (root == root->parent->left) {
				root->parent->left = tree->nil;
			}
			else {
				root->parent->right = tree->nil;
			}
			free(root);
		}
		else { // 不是叶子节点
			destoryRBTree(tree, root->left);
			destoryRBTree(tree, root->right);
			if (root->parent == tree->nil) { // root 为根节点
				free(root);
				free(tree->nil);
				free(tree);
			}
			else { // root 不是根节点，free root，然后将节点指向 root 的子树置为 nil
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
* 红黑树的中序遍历
*/
void RBTreeMiddleTraverse(PRBTree tree, PRBTreeNode root) {
	if (root != tree->nil) {
		RBTreeMiddleTraverse(tree, root->left);
		if (root->color == RED) {
			printf("红 ");
		}
		else {
			printf("黑 ");
		}
		printf("%d ", root->key);
		RBTreeMiddleTraverse(tree, root->right);
	}
}

/**
* 打印指定层数的数
* @param root 根节点
* @param currentLevel 当前层
* @param level 需要打印的层数节点
*/
void printLevel(PRBTree tree, PRBTreeNode root, int currentLevel, int level, int space) {
	if (root != tree->nil) {
		if (currentLevel == level) { // 到达对应的层数
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
		else { // 还没到,继续往下找
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
* 层序遍历，更直观的看出树的形状
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
* 校验规则1和3，
* 1.对于红黑树来说，每个节点，要么是红色，要么是黑色
* 3. 叶节点 nil 是黑色的
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
* 校验规则4：如果一个节点是红色的，那么他的两个字点都是黑色的
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
	else { // nil 不需要校验，直接返回成功
		return 1;
	}
}


/**
* 计算红黑树所有的叶子节点，将其保存在 list 中
*/
void getAllLeafNodesR(PRBTree tree, PRBTreeNode root, PRBTreeNodeList *list) {
	
	if (root != tree->nil) {
		// 根节点不为空，且左右子树都为空时，为叶节点
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
* 获取红黑树所有的叶子节点，使用链表的形式返回
*/
PRBTreeNodeList getAllLeafNodes(PRBTree tree, PRBTreeNode root) {
	PRBTreeNodeList list = NULL;
	getAllLeafNodesR(tree, root, &list);
	return list;
}

/**
* 从节点 root 到达 节点 target 需要经历的黑色节点数
* 如果从节点 root 无法通过左子树或右子树到达 target, 返回 -1，表示不可达
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
		else { // 找到了
			return  blackNodes + currentBlackNodes;
		}
	}
	else { // 没找到
		return -1;
	}
}

/**
* 校验根节点到所有叶子节点经过的黑色节点数，比较是否相等，如果都相等，返回1，否则返回0
* 对于不可达的节点，使用 -1 表示，不需要校验
*/
int validRootReachEachLeaves(PRBTree tree, PRBTreeNode root, PRBTreeNodeList leaves, int leavesSize) {
	int* res = (int*)malloc(sizeof(int) * leavesSize);
	PRBTreeNodeList p = leaves;
	int previous = -1;
	while (p != NULL) {
		int blackNodes = clcReachLeavesBlackNodes(tree, root, p->node, 0);
		if (blackNodes != -1) {
			if (previous == -1) { // 第一次遇到可达的叶子节点
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
* 计算红黑树所有的非叶子节点到所有叶子节点的简单路径的黑色根节点数量
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
* 校验规则 5：对每个节点，到其所有后代的叶节点的简单路径上，均包含相同数目的黑色节点
* @return 该节点到左右子树的黑色节点数
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
* 校验一棵红黑树是否符合以下红黑树的规则
* 1. 每个节点，要么是红色，要么是黑色
* 2. 根节点是黑色的
* 3. 每个叶节点 nil 是黑色的
* 4. 如果一个节点是红色的，那么他的两个字点都是黑色的
* 5. 对每个节点，到其所有后代的叶节点的简单路径上，均包含相同数目的黑色节点
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

