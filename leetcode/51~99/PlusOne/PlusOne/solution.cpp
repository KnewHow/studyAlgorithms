#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int size = digits.size();
        int extra = 1; // ��λ
        for (int j = size - 1; j>=0; j--) {
            if (extra < 1) {
                break;
            }
            else {
                int n = digits.at(j);
                int newN = n + extra;
                digits.at(j) = newN % 10;
                extra = newN / 10;
            }
        }
        // ���ѭ���������н�λ����ʾ����������һλ����Ҫ��ǰ��+1 λ
        if (extra > 0) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
    void printDigits(vector<int> digits) {
        cout << "[";
        for (auto b = digits.begin(); b != digits.end(); b++) {
            if (b == digits.end() - 1) {
                cout << *b;
            }
            else {
                cout << *b << ", ";
            }
        }
        cout << " ]" << endl;
    }
};