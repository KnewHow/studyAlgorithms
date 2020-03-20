#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


/*define a binary tree*/
typedef struct AVLTree {
    int key;
    struct AVLTree* left;
    struct AVLTree* right;
    int treeHeight;/*为了平衡二叉树计算方便，定义树高*/
}AVLTree, *PAVLTree;

/*二叉搜索树的递归查找*/
PAVLTree AVLTreeSearch(int key, PAVLTree root) {
    if (!root) {
        return NULL;
    }
    if (key < root->key) {
        /*查找元素比根元素小在左子树中查找*/
        return  AVLTreeSearch(key, root->left);
    }
    else if (key > root->key) {
        /*查找元素比根元素小在右子树中查找*/
        return AVLTreeSearch(key, root->right);
    }
    else {/*找到该节点，返回*/
        return root;
    }
}

/*根据二叉搜索树的特点，最小元素在最左边的节点上面*/
PAVLTree getAVLTreeMin(PAVLTree root) {
    if (root) {
        while (root->left) {
            root = root->left;
        }
    }

    return root;
}

/*获取二叉搜索树中的最大元素，最大元素的位置应该在最右边的节点上*/
PAVLTree getAVLTreeMax(PAVLTree root) {
    if (root) {
        while (root->right) {
            root = root->right;
        }
    }

    return root;
}



/*获取二叉树的树高*/
int getHeight(PAVLTree tree) {
    if (tree) {
        int lh = getHeight(tree->left);
        int rh = getHeight(tree->right);
        return max(lh, rh) + 1;
    }
    return 0;
}
/*
左单旋操作：将A与B进行LL旋转，并更新A和B的新高度，返回新的根节点B
A必须有一个左子节点B
*/
PAVLTree singleLeftRatation(PAVLTree A) {
    PAVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->treeHeight = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->treeHeight = max(B->left, A->treeHeight) + 1;
    return B;
}

/*右单旋:将A与B进行RR旋转，并更新A与B的高度,返回新的根节点B
注：A必须有一个右节点B
*/
PAVLTree singleRightRatation(PAVLTree A) {
    PAVLTree B = A->right;
    A->right = B->left;
    B->left = A;
    A->treeHeight = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->treeHeight = max(getHeight(B->right), A->treeHeight);
    return B;
}

/*
将A做LR旋转，返回新的根节点C
A必须有一个左自己的B，B必须有一个右子节点C
*/
PAVLTree doubleLeftRightRatation(PAVLTree A) {
    /*先对B，C进行RR旋转,C被返回*/
    A->left = singleRightRatation(A->left);
    /*在对A和C进行LL旋转，返回新的根节点C*/
    return singleLeftRatation(A);
}

/*
对A进行RL旋转，返回新的根节点C
注：A必须有一个右子节点B，B必须有一个左子节点C
*/
PAVLTree doubleRightLeftRatation(PAVLTree A) {
    /*先对B，C进行LL旋转,返回新的根节点C*/
    A->right = singleLeftRatation(A->right);
    /*在对A，C进行RR旋转，返回新的根节点C*/
    return singleRightRatation(A);
}

/*对二叉搜索树进行插入，插入后调整树的平衡*/
PAVLTree AVLInsert(PAVLTree tree, int key) {
    if (!tree) {
        tree = (PAVLTree)malloc(sizeof(AVLTree));
        tree->key = key;
        tree->left = tree->right = NULL;
        tree->treeHeight = 0;
    }
    else if (key < tree->key) {
        tree->left = AVLInsert(tree->left, key);
        //判断平衡因子是否等于2
        if (getHeight(tree->left) - getHeight(tree->right) == 2) {
            if (key < tree->left->key) {//key往tree的左子树的左子树插入导致平衡因子大于2，进行LL调整的
                tree = singleLeftRatation(tree);
            }
            else {//key往tree的左子树的右子树插入导致平衡因子大于2，进行LR调整
                tree = doubleLeftRightRatation(tree);
            }
        }
    }
    else if (key > tree->key) {
        tree->right = AVLInsert(tree->right, key);
        //判断平衡因子是否等于2
        if (getHeight(tree->right) - getHeight(tree->left) == 2) {
            if (key > tree->right->key) {//key往tree的右子树的右子树插入导致平衡因子大于2，进行RR调整
                tree = singleRightRatation(tree);
            }
            else {//key往tree的右子树的左子树插入导致平衡因子大于2，进行RL调整
                tree = doubleRightLeftRatation(tree);
            }
        }
    }/* else 如果找到了，就不进行插入*/

    tree->treeHeight = max(getHeight(tree->left), (getHeight(tree->right))) + 1;
    return tree;
}

PAVLTree AVLDelete(PAVLTree tree, int key) {
    PAVLTree temp;
    if (!tree) {
        printf("not found key in this tree\n");
    }
    else if (key < tree->key) {
        tree->left = AVLDelete(tree->left, key);
    }
    else if (key > tree->key) {
        tree->right = AVLDelete(tree->right, key);
    }
    else {//找到需要删除的元素节点
        if (tree->left && tree->right) {//该有两个孩子节点
            temp = getAVLTreeMin(tree->right);/*获取右子树的最小值节点*/
            tree->key = temp->key;
            tree->right = AVLDelete(tree->right, temp->key);
        }
        else {
            temp = tree;
            if (!tree->left) {
                tree = tree->right;
            }
            else if (!tree->right) {
                tree = tree->left;
            }
            free(temp);
        }
    }
    return tree;
}
