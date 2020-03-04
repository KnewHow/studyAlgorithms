#include<stdlib.h>
#include<stdio.h>

// ��ʾ��`i`�У�����`j`�����˶��ٴ�
int rows[9][10] = { 0 };
// ��ʾ��`i`�У�����`j`�����˶��ٴ�
int cols[9][10] = { 0 };

// ��ʾ��`i`�� sub box�� ����`j`�����˶��ٴ�
// ��������� board[i][j],���ǿ���֪�������� �� `i/3 *3 + j / 3` subBox
int subBox[9][10] = { 0 };

// ��ʾboard[i][j]�� Ԫ���Ƿ���Ի��� 0-������ 1-����
int tag[9][9] = { 0 };


// ���ݸ����� board,�������������г�ʼ��
void initArray(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < *(boardColSize + i); j++) {
			char c = *(*(board + i) + j);
			if (c == '.') {
				tag[i][j] = 1;
			}
			else {
				int number = c - 48;
				rows[i][number] = 1;
				cols[j][number] = 1;
				int subBoxIndex = i / 3 * 3 + j / 3;
				subBox[subBoxIndex][number] = 1;
				tag[i][j] = 0;
			}
		}
	}
}

/**
* �� 1~9 ���Ҵ���ʵ�k �����i�У���j�еķ����У�����Ҳ������ҳ�����Ļ��ݵ�
* @param board ԭ��������
* @param nth �� nth ����
* @param i �� i ��
* @param j �� j ��
* @param subBoxesIndex �ӷ���ĽǱ�
* @param kInitValue k �ĳ�ʼֵ
* @param m ���ݵ��� m �е�ָ��
* @param n ���ݵ��� n �е�ָ��
* @param minReCallNth ���ݵ��� minReCallNth �����ָ��
*/
void findK(
	char** board, 
	int nth, 
	int i, 
	int j, 
	int subBoxIndex,
	int kInitValue,
	int *m,
	int *n,
	int * minReCallNth
) {
	int isFind = 0;
	for (int k = kInitValue; k <= 9; k++) {
		// ��������
		if (rows[i][k] == 0 && cols[j][k] == 0
			&& subBox[subBoxIndex][k] == 0) {
			char number = k + 48;
			*(*(board + i) + j) = number;
			rows[i][k] = 1;
			cols[j][k] = 1;
			subBox[subBoxIndex][k] = 1;
			isFind = 1;
			// �ҵ����ϵģ��ͽ�֮ǰ�Ĳ����ϵ����
			break;
		}		
	}

	if (isFind == 1) {
		*m = -1;
		*n = -1;
		*minReCallNth = INT_MAX;
	}
	else {
		// �������һ���ɻ��ݵ㣬Ȼ�����
		for (int counter = nth - 1; counter >= 0; counter--) {
			int x = counter / 9;
			int y = counter % 9;
			if (tag[x][y] == 1) { // �ɻ���
				*m = x;
				*n = y;
				*minReCallNth = counter;
				break;
			}
		}
	}
}


/**
* @param nth ����Ϊ���ȱ������� 0 ��ʼ���� 80 ��������ʾ���㵽�� nth ������
*/
void solve(char** board, int boardSize, int* boardColSize, int nth) {
	long long int callCounter = 0;
	while (nth <= 80) {
		callCounter++;
		int i = nth / boardSize;
		int j = nth % *(boardColSize + i);
		int subBoxIndex = i / 3 * 3 + j / 3;
		char c = *(*(board + i) + j);
		// ���ݹ������ m,�� n,�Լ����ǵڼ�������
		int m = -1;
		int n = -1;
		int minReCallNth = INT_MAX;
		if (c == '.') {
			findK(board, nth, i, j, subBoxIndex, 1, &m, &n, &minReCallNth);
			// ����ҵ����֣��������������
			if (m == -1 && n == -1) {
				nth++;
			}
			else { // û�ҵ�������
				nth = minReCallNth;
			}
		}
		else {// ������� . ��������� 1.��Ŀ������ֵ�������κβ�����2.��������
			if (tag[i][j] == 0) { // ���ɻ��ݣ�����
				nth++;
			}
			else { // �� number+1 ~ 9 ���¼��� k ��ֵ
				int k = c - 48;
				rows[i][k] = 0;
				cols[j][k] = 0;
				subBox[subBoxIndex][k] = 0;
				*(*(board + i) + j) = '.';
				// �ýڵ��޷������ˣ���Ҫ����������һ����
				if (k == 9) { 
					// �������һ���ɻ��ݵ㣬Ȼ�����
					for (int counter = nth - 1; counter >= 0; counter--) {
						int x = counter / boardSize;
						int y = counter % *(boardColSize + x);
						if (tag[x][y] == 1) {
							nth = counter;
							break;
						}
					}
				}
				else {
					findK(board, nth, i, j, subBoxIndex, k + 1, &m, &n, &minReCallNth);
					// ����ҵ����֣��������������
					if (m == -1 && n == -1) {
						nth++;
					}
					else { // û�ҵ�������
						nth = minReCallNth;
					}
				}
			}
		}
	}
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
	initArray(board, boardSize, boardColSize);
	solve(board, boardSize, boardColSize, 0);
}

void printBoard(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < boardSize; i++) {
		char* s = *(board + i);
		for (int j = 0; j < *(boardColSize + i); j++) {
			printf("%c ", *(s + j));
		}
		printf("\n");
	}
}

char** initBoard(char b[][9]) {
	char** board = (char**)malloc(sizeof(char*) * 9);
	for (int i = 0; i < 9; i++) {
		char* s1 = (char*)malloc(sizeof(char) * 10);
		int j = 0;
		for (; j < 9; j++) {
			*(s1 + j) = b[i][j];
		}
		*(s1 + j) = '\0';
		*(board + i) = s1;
	}
	return board;
}

int main() {
	char b[][9] = {
		{'.','.','9','7','4','8','.','.','.'},
		{'7','.','.','.','.','.','.','.','.'},
		{'.','2','.','1','.','9','.','.','.'},
		{'.','.','7','.','.','.','2','4','.'},
		{'.','6','4','.','1','.','5','9','.'},
		{'.','9','8','.','.','.','3','.','.'},
		{'.','.','.','8','.','3','.','2','.'},
		{'.','.','.','.','.','.','.','.','6'},
		{'.','.','.','2','7','5','9','.','.'}
	};
	char** board = initBoard(&b);
	int boardSize = 9;
	int boardColSize[9] = { 0 };
	for (int i = 0; i < boardSize; i++) {
		boardColSize[i] = 9;
	}
	printBoard(board, boardSize, boardColSize);
	solveSudoku(board, boardSize, boardColSize);
	printBoard(board, boardSize, boardColSize);
	system("pause");
	return 0;
}