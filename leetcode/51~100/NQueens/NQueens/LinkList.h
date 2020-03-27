#pragma once
#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
// Á´±í½Úµã
typedef struct LinkListNode {
	char* key;
	char* value;
	struct LinkListNode* next;
} LinkListNode, * PLinkListNode;

typedef struct LinkList {
	PLinkListNode root;
	PLinkListNode nil;
}LinkList, * PLinkList;

PLinkList newLinkList() {
	PLinkList list = (PLinkList)malloc(sizeof(LinkList));
	PLinkListNode nil = (PLinkListNode)malloc(sizeof(LinkListNode));
	nil->key = '\0';
	nil->value = 0;
	nil->next = nil;
	list->nil = nil;
	list->root = nil;
	return list;
}

PLinkListNode newLinkListNode(PLinkList list, char* key, char* value) {
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

PLinkListNode linkListGet(PLinkList list, char* key) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		if (strcmp(root->key, key) == 0) {
			return root;
		}
		root = root->next;
	}
	return list->nil;
}

void linkListRemove(PLinkList list, char* key) {
	PLinkListNode root = list->root;
	PLinkListNode previous = list->nil;
	while (root != list->nil) {
		if (strcmp(root->key, key) != 0) {
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

void printLinkList(PLinkList list) {
	PLinkListNode root = list->root;
	while (root != list->nil) {
		printf("%s->", root->key);
		root = root->next;
	}
	printf("null\n");
}