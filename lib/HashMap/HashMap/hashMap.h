#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"RBTree.h"
#include"LinkList.h"
#define LINK_LIST_WAY 0
#define RB_TREE_WAY 1
#define N 1024
#define LINK_LIST_MAX 10

typedef struct HashTable {
	int way; // 0-Á´±í 1-ºìºÚÊ÷
	PLinkList list;
	PRBTree tree;
	int size;
} HashTable, *PHashTable;

typedef struct HashMap {
	int size;
	PHashTable* tables;
}HashMap, *PHashMap;

PHashTable newHashTable() {
	PHashTable hashTable = (PHashTable)malloc(sizeof(HashTable));
	PRBTree tree = newRBTree();
	PLinkList list = newLinkList();
	hashTable->list = list;
	hashTable->tree = tree;
	hashTable->size = 0;
}

PHashMap newHashMap() {
	PHashMap hashMap = (PHashMap)malloc(sizeof(HashMap));
	PHashTable* tables = (PHashTable*)malloc(sizeof(PHashTable) * N);
	for (int i = 0; i < N; i++) {
		*(tables + i) = NULL;
	}
	hashMap->size = 0;
	hashMap->tables = tables;
	return hashMap;
}

int hashCode(int key) {
	return key;
}

void linkListToRBTree(PHashTable table) {
	PLinkList list = table->list;
	PLinkListNode  root = list->root;
	while (root != list->nil) {
		PLinkListNode temp = root;
		root = root->next;
		PRBTreeNode node = newRBTreeNode(table->tree, temp->key, temp->value);
		RBInsert(table->tree, node);
		free(temp);
	}
	table->list->root = table->list->nil;
	table->way = RB_TREE_WAY;
}


void hashTablePut(PHashMap map, int key, int value) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table == NULL) {
		PHashTable table = newHashTable();
		table->way = LINK_LIST_WAY;
		PLinkListNode node = newLinkListNode(table->list, key, value);
		linkListPut(table->list, node);
		table->size = 1;
		*(map->tables + pos) = table;
	}
	else {
		if (table->way == RB_TREE_WAY) {
			PRBTreeNode node = newRBTreeNode(table->tree, key, value);
			RBInsert(table->tree, node);
			table->size = table->size + 1;
		}
		else {
			if (table->size + 1 > LINK_LIST_MAX) {
				linkListToRBTree(table);
				PRBTreeNode node = newRBTreeNode(table->tree, key, value);
				RBInsert(table->tree, node);
				table->size = table->size + 1;
			}
			else {
				PLinkListNode node = newLinkListNode(table->list, key, value);
				linkListPut(table->list, node);
				table->size = table->size + 1;
			}
		}
	}
}

int hashTableGetOrElse(PHashMap map, int key, int defaultV) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table->way == LINK_LIST_WAY) {
		PLinkListNode node = linkListGet(table->list, key);
		if (node != table->list->nil) {
			return node->value;
		}
		else {
			return defaultV;
		}

	}
	else {
		PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
		if (node != table->tree->nil) {
			return node->value;
		}
		else {
			return defaultV;
		}
	}
}

int hashTableContains(PHashMap map, int key) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table->way == LINK_LIST_WAY) {
		PLinkListNode node = linkListGet(table->list, key);
		if (node != table->list->nil) {
			return 1;
		}
		else {
			return 0;
		}

	}
	else {
		PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
		if (node != table->tree->nil) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

void hashTableRemove(PHashMap map, int key) {
	int pos = hashCode(key) % N;
	PHashTable table = *(map->tables + pos);
	if (table->way == LINK_LIST_WAY) {
		linkListRemove(table->list, key);
	}
	else {
		PRBTreeNode node = RBGetByKey(table->tree, table->tree->root, key);
		if (node != table->tree->nil) {
			RBRemove(table->tree, node);
		}
	}
}

void destoryHashMap(PHashMap map) {
	PHashTable* tables = map->tables;
	for (int i = 0; i < N; i++) {
		PHashTable table = *(tables + i);
		if (table != NULL) {
			destoryLinkList(table->list);
			destoryRBTree(table->tree);
			free(table);
		}
	}
	free(tables);
	free(map);
}


