#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

// Á´±í½Úµã
typedef struct LinkListNode {
	int key;
	int value;
	struct LinkListNode* next;
} LinkListNode, *PLinkListNode;

typedef struct LinkList {
	PLinkListNode root;
	PLinkListNode nil;
}LinkList, *PLinkList;

PLinkList newLinkList() {
	PLinkList list = (PLinkList)malloc(sizeof(LinkList));
	PLinkListNode nil = (PLinkListNode)malloc(sizeof(LinkListNode));
	nil->key = 0;
	nil->value = 0;
	nil->next = nil;
	list->nil = nil;
	list->root = nil;
	return list;
}

PLinkListNode newLinkListNode(PLinkList list, int key, int value) {
	PLinkListNode node = (PLinkListNode)malloc(sizeof(LinkListNode));
	node->key = key;
	node->value = value;
	node->next = list->nil;
	return node;
}

void linkListPut(PLinkList list, PLinkListNode node) {
	if (list->root == NULL) {
		list->root = node;
		node->next = list->nil;
	}
	else {
		node->next = list->root;
		list->root = node;
	}
}

PLinkListNode linkListGet(PLinkList list, int key) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		if (root->key == key) {
			return root;
		}
		root = root->next;
	}
	return list->nil;
}

void linkListRemove(PLinkList list, int key) {
	PLinkListNode root = list->root;
	PLinkListNode previous = list->nil;
	while (root != list->nil) {
		if (root->key != key) {
			previous = root;
			root = root->next;
		}
		else {
			if (previous == list->nil) { // remove root
				list->root = root->next;
				free(root);
				return;
			}
			else {
				previous->next = root->next;
				free(root);
				return;
			}
		}
	}
}

void destoryLinkList(PLinkList list) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		PLinkListNode temp = root;
		root = root->next;
		free(temp);
	}
	free(list->nil);
	free(list);
}