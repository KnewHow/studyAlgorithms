#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


/*define a binary tree*/
typedef struct AVLTree {
    int key;
    struct AVLTree* left;
    struct AVLTree* right;
    int treeHeight;/*Ϊ��ƽ����������㷽�㣬��������*/
}AVLTree, *PAVLTree;

/*�����������ĵݹ����*/
PAVLTree AVLTreeSearch(int key, PAVLTree root) {
    if (!root) {
        return NULL;
    }
    if (key < root->key) {
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return  AVLTreeSearch(key, root->left);
    }
    else if (key > root->key) {
        /*����Ԫ�رȸ�Ԫ��С���������в���*/
        return AVLTreeSearch(key, root->right);
    }
    else {/*�ҵ��ýڵ㣬����*/
        return root;
    }
}

/*���ݶ������������ص㣬��СԪ��������ߵĽڵ�����*/
PAVLTree getAVLTreeMin(PAVLTree root) {
    if (root) {
        while (root->left) {
            root = root->left;
        }
    }

    return root;
}

/*��ȡ�����������е����Ԫ�أ����Ԫ�ص�λ��Ӧ�������ұߵĽڵ���*/
PAVLTree getAVLTreeMax(PAVLTree root) {
    if (root) {
        while (root->right) {
            root = root->right;
        }
    }

    return root;
}



/*��ȡ������������*/
int getHeight(PAVLTree tree) {
    if (tree) {
        int lh = getHeight(tree->left);
        int rh = getHeight(tree->right);
        return max(lh, rh) + 1;
    }
    return 0;
}
/*
������������A��B����LL��ת��������A��B���¸߶ȣ������µĸ��ڵ�B
A������һ�����ӽڵ�B
*/
PAVLTree singleLeftRatation(PAVLTree A) {
    PAVLTree B = A->left;
    A->left = B->right;
    B->right = A;
    A->treeHeight = max(getHeight(A->left), getHeight(A->right)) + 1;
    B->treeHeight = max(B->left, A->treeHeight) + 1;
    return B;
}

/*�ҵ���:��A��B����RR��ת��������A��B�ĸ߶�,�����µĸ��ڵ�B
ע��A������һ���ҽڵ�B
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
��A��LR��ת�������µĸ��ڵ�C
A������һ�����Լ���B��B������һ�����ӽڵ�C
*/
PAVLTree doubleLeftRightRatation(PAVLTree A) {
    /*�ȶ�B��C����RR��ת,C������*/
    A->left = singleRightRatation(A->left);
    /*�ڶ�A��C����LL��ת�������µĸ��ڵ�C*/
    return singleLeftRatation(A);
}

/*
��A����RL��ת�������µĸ��ڵ�C
ע��A������һ�����ӽڵ�B��B������һ�����ӽڵ�C
*/
PAVLTree doubleRightLeftRatation(PAVLTree A) {
    /*�ȶ�B��C����LL��ת,�����µĸ��ڵ�C*/
    A->right = singleLeftRatation(A->right);
    /*�ڶ�A��C����RR��ת�������µĸ��ڵ�C*/
    return singleRightRatation(A);
}

/*�Զ������������в��룬������������ƽ��*/
PAVLTree AVLInsert(PAVLTree tree, int key) {
    if (!tree) {
        tree = (PAVLTree)malloc(sizeof(AVLTree));
        tree->key = key;
        tree->left = tree->right = NULL;
        tree->treeHeight = 0;
    }
    else if (key < tree->key) {
        tree->left = AVLInsert(tree->left, key);
        //�ж�ƽ�������Ƿ����2
        if (getHeight(tree->left) - getHeight(tree->right) == 2) {
            if (key < tree->left->key) {//key��tree�������������������뵼��ƽ�����Ӵ���2������LL������
                tree = singleLeftRatation(tree);
            }
            else {//key��tree�������������������뵼��ƽ�����Ӵ���2������LR����
                tree = doubleLeftRightRatation(tree);
            }
        }
    }
    else if (key > tree->key) {
        tree->right = AVLInsert(tree->right, key);
        //�ж�ƽ�������Ƿ����2
        if (getHeight(tree->right) - getHeight(tree->left) == 2) {
            if (key > tree->right->key) {//key��tree�������������������뵼��ƽ�����Ӵ���2������RR����
                tree = singleRightRatation(tree);
            }
            else {//key��tree�������������������뵼��ƽ�����Ӵ���2������RL����
                tree = doubleRightLeftRatation(tree);
            }
        }
    }/* else ����ҵ��ˣ��Ͳ����в���*/

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
    else {//�ҵ���Ҫɾ����Ԫ�ؽڵ�
        if (tree->left && tree->right) {//�����������ӽڵ�
            temp = getAVLTreeMin(tree->right);/*��ȡ����������Сֵ�ڵ�*/
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
