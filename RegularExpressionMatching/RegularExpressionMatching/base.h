#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

// ÿ�ε�ƥ����
typedef struct MatchResult {
	int begin; // �´ο�ʼ�� index 
	int isMatch; // ����Ƿ�ƥ�� 1-ƥ�� 0-��ƥ��
} MatchResult, * PMatchResult;

PMatchResult createMatchResult(int begin, int isMatch) {
	PMatchResult r = (PMatchResult)malloc(sizeof(MatchResult));
	r->begin = begin;
	r->isMatch = isMatch;
	return r;
}
