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
	int height; // 树高
}RBTree, *PRBTree;

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
* 红黑树的高度
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
	// 重新计算树高
	tree->height = getHeight(tree, tree->root);
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
		else { // 还没到,继续往下找
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
* 层序遍历，更直观的看出树的形状
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
			r && validRule4(tree, root->left) && validRule4(tree, root->right);
		}
	}
	else { // nil 不需要校验，直接返回成功
		return 1;
	}
}

/**
* 校验规则 5：对每个节点，到其所有后代的叶节点的简单路径上，均包含相同数目的黑色节点
* @return 该节点到左右子树的黑色节点数
*/
int validRule5(PRBTree tree, PRBTreeNode root, int *returnR5) {
	if (root != tree->nil) {
		int lb = validRule5(tree, root->left, returnR5);
		int rb = validRule5(tree, root->right, returnR5);
		// 校验失败
		if (lb != rb) {
			printf("root node key: %d left blacks: %d, and rigth black :%d not equal\n", root->key, lb, rb);
			*returnR5 = 0;
			// 这个返回已经其实已经无所谓了
			return lb;
		}
		else {
			if (root->color == BLACK) { // 如果该节点本身是黑色节点 +1，否则只返回子树的黑色节点数
				return 1 + lb;
			}
			else {
				return lb;
			}
		}
		
	}
	else { // nil 算一个黑节点
		return 1;
	}
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
	int r5 = 1;
	validRule5(tree, tree->root, &r5);
	return r13 && r2 && r4 & r5;;
}

