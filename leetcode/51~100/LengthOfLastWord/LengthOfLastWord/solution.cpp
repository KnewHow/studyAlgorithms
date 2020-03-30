#include<string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        if (s.empty()) {
            return 0;
        }
        else {
            int size = 0;
            // �Ƿ�����˵�һ���ǿո���ַ�
            bool isAlphabet = false;
            for (auto end = s.end() - 1; end >= s.begin(); end--) {
                char c = *end;
                if (c == ' ' && !isAlphabet) {
                    continue;
                }
                if (c == ' ' && isAlphabet) {
                    return size;
                }
                else {
                    isAlphabet = true;
                    size++;
                }
                if (end == s.begin()) {
                    break;
                }
            }
            return size;
        }
    }
};