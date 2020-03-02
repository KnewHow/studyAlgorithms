# Valid Sudoku

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated **according to the following rules**:

* Each row must contain the digits 1-9 without repetition.
* Each column must contain the digits 1-9 without repetition.
* Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.



![](250px-Sudoku-by-L2G-20050714.svg.png)

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:

```
Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
```

Example 2:

```
Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
```

Note:

* A Sudoku board (partially filled) could be valid but is not necessarily solvable. 
* Only the filled cells need to be validated according to the mentioned rules.
* The given board contain only digits 1-9 and the character '.'
* The given board size is always 9x9.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-sudoku
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# Solution

似乎没想到其它什么好办法，只能暴力的去校验了

```c
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
```

在官方的题解中，可以利用 hashMap 来减少遍历的次数，只需要遍历 81 次即可，https://leetcode-cn.com/problems/valid-sudoku/solution/you-xiao-de-shu-du-by-leetcode/