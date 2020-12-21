#include<vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix = vector<vector<int>>();
        for (int i = 0; i < n; i++) {
            vector<int> row = vector<int>();
            for (int j = 0; j < n; j++) {
                row.push_back(0);
            }
            matrix.push_back(row);
        }
        int begin = 0;
        int row = n;
        int col = n;
        int current = 1;
        while (row > 0 && col > 0) {
            doSpiral(matrix, begin, begin, row, col, current);
            begin++;
            row -= 2;
            col -= 2;
        }
        return matrix;
    }
    /**
    * �Ծ����������
    * @param matrix ԭ�ȵľ���
    * @param beginRow ��ʼ��
    * @param beginCol ��ʼ��
    * @param ����� row �ĳ���
    * @param ����� col �ĳ���
    * @param r ���յĽ��
    */
    void doSpiral(vector<vector<int>>& matrix, int beginRow, int beginCol, int row, int col, int &current) {
        //��һ��
        for (int i = beginCol; i < beginCol + col; i++) {
            matrix[beginRow][i] = current++;
        }
        // ���һ��,�����ų���һ��Ԫ��
        int lastColNumber = beginCol + col - 1;
        for (int i = beginRow + 1; i < beginRow + row; i++) {
            matrix[i][lastColNumber] = current++;
        }
        // ���һ�У������ų����һ��Ԫ��
        int lastRowNumber = beginRow + row - 1;
        if (row > 1) { // ��row > 1��ʱ���ִ�У����һ�к͵�һ�вŲ����ظ�
            for (int i = lastColNumber - 1; i >= beginCol; i--) {
               matrix[lastRowNumber][i] = current++;
            }
        }
        if (col > 1) { // �� col > 1����һ�к����һ�вŲ����ظ�
            // ��һ�У����ų����һ��Ԫ�غ͵�һ��Ԫ��
            for (int i = lastRowNumber - 1; i > beginRow; i--) {
                matrix[i][beginCol] = current++;
            }
        }

    }
};