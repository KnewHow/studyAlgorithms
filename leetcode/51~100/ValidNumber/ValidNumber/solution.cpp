#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    int getId(char c) {
        if (c == ' ') {
            return 0;
        }
        else if (c == '-' || c == '+') {
            return 1;
        }
        else if (c == '.') {
            return 3;
        }
        else if (c == 'e') {
            return 4;
        }
        else if (c >= '0' && c <= '9') {
            return 2;
        }
        else {
            return -1;
        }
    }
    bool isNumber(string s) {
        int states[9][5] = { 
            { 0, 1, 6, 2,-1},
            {-1,-1, 6, 2,-1},
            {-1,-1, 3,-1,-1},
            { 8,-1, 3,-1, 4},
            {-1, 7, 5,-1,-1},
            { 8,-1, 5,-1,-1},
            { 8,-1, 6, 3, 4},
            {-1,-1, 5,-1,-1},
            { 8,-1,-1,-1,-1} 
        };
        // 最终状态只有 3、5、6、8 状态才为合法状态
        int finals[] = { 0, 0, 0, 1, 0, 1, 1, 0, 1 };
        int state = 0;
        for (auto begin = s.begin(); begin != s.end(); begin++) {
            char c = *begin;
            int id = getId(c);
            if (id < 0) {
                return false;
            }
            state = states[state][id];
            if (state < 0) {
                return false;
            }
        }
        return finals[state] > 0;

    }
};