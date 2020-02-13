#pragma once
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>

// 每次的匹配结果
typedef struct MatchResult {
	int begin; // 下次开始的 index 
	int isMatch; // 这次是否匹配 1-匹配 0-不匹配
} MatchResult, * PMatchResult;

PMatchResult createMatchResult(int begin, int isMatch) {
	PMatchResult r = (PMatchResult)malloc(sizeof(MatchResult));
	r->begin = begin;
	r->isMatch = isMatch;
	return r;
}
