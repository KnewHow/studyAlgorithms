#include<vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row = matrix.size();
        vector<int> r = vector<int>();
        if (row == 0) {
            return r;
        }
        else {
            vector<int> first = matrix.front();
            int col = first.size();
            int begin = 0;
            while (row > 0 && col > 0) {
                doSpiral(matrix, begin, begin, row, col, r);
                begin++;
                row -= 2;
                col -= 2;
            }
            return r;
        }
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
    void doSpiral(vector<vector<int>>& matrix, int beginRow, int beginCol, int row, int col, vector<int>& r) {
        //��һ��
        for (int i = beginCol; i < beginCol + col; i++) {
            int v = matrix[beginRow][i];
            r.push_back(v);
        }
        // ���һ��,�����ų���һ��Ԫ��
        int lastColNumber = beginCol + col - 1;
        for (int i = beginRow + 1; i < beginRow + row; i++) {
            int v = matrix[i][lastColNumber];
            r.push_back(v);
        }
        // ���һ�У������ų����һ��Ԫ��
        int lastRowNumber = beginRow + row - 1;
        if (row > 1) { // ��row > 1��ʱ���ִ�У����һ�к͵�һ�вŲ����ظ�
            for (int i = lastColNumber - 1; i >= beginCol; i--) {
                int v = matrix[lastRowNumber][i];
                r.push_back(v);
            }
        }
        if (col > 1) { // �� col > 1����һ�к����һ�вŲ����ظ�
            // ��һ�У����ų����һ��Ԫ�غ͵�һ��Ԫ��
            for (int i = lastRowNumber - 1; i > beginRow; i--) {
                int v = matrix[i][beginCol];
                r.push_back(v);
            }
        }
    }
};