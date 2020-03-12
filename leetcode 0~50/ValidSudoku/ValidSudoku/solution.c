#include<stdlib.h>
#include<stdio.h>

int validArray[10] = { 0 };

void initValidArray() {
	for (int i = 0; i < 10; i++) {
		validArray[i] = -1;
	}
}

int validRow(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		initValidArray();
		char* row = *(board + i);
		for (int j = 0; j < *(boardColSize + i); j++) {
			char c = *(row + j);
			if (c == '.') {
				continue;
			}
			else {
				int number = c - 48;
				// 重复出现
				if (validArray[number] != -1) {
					return 0;
				}
				else {
					validArray[number] = 1;
				}
			}
		}
	}
	return 1;
}

// 校验列
int validCol(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		initValidArray();
		for (int j = 0; j < *(boardColSize + i); j++) {
			char c = *(*(board + j) + i);
			if (c == '.') {
				continue;
			}
			else {
				int number = c - 48;
				if (validArray[number] != -1) {
					return 0;
				}
				else {
					validArray[number] = 1;
				}
			}
			
		}
	}
	return 1;
}

// 校验 sub boxes
int validSubBoxes(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		int counter = i / 3;
		int beginRow = counter * 3;
		int beginCol = (i % 3) * 3;
		initValidArray();
		for (int row = beginRow; row < beginRow + 3; row++) {
			for (int col = beginCol; col < beginCol + 3; col++) {
				char c = *(*(board + row) + col);
				if (c == '.') {
					continue;
				}
				else {
					int number = c - 48;
					if (validArray[number] != -1) {
						return 0;
					} else {
						validArray[number] = 1;
					}
				}
			}
		}
	}
	return 1;
}

int isValidSudoku(char** board, int boardSize, int* boardColSize) {
	return validCol(board, boardSize, boardColSize)
		&& validRow(board, boardSize, boardColSize)
		&& validSubBoxes(board, boardSize, boardColSize);
}

int main() {
	char* board[] = {
		"83..7....",
		"6..195...",
		".98....6.",
		"8...6...3",
		"4..8.3..1",
		"7...2...6",
		".6....28.",
		"...419..5",
		"....8..79"
	};
	int boardSize = 9;
	int boardColSize[9] = { 0 };
	for (int i = 0; i < boardSize; i++) {
		boardColSize[i] = 9;
	}
	int r = isValidSudoku(board, boardSize, boardColSize);
	printf("r is:%d\n", r);
	system("pause");
	return 0;
}