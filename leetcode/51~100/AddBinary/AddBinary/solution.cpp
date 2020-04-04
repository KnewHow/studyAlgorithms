#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        vector<int> rv = vector<int>();
        int e1 = a.size()-1;
        int e2 = b.size()-1;
        int extra = 0; // ½øÎ»
        while (e1 >=0 || e2 >=0) {
            if (e1 >= 0 && e2 >= 0) {
                int n1 = a.at(e1) - 48;
                int n2 = b.at(e2) - 48;
                int n = n1 + n2 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e1--;
                e2--;
            }
            else if (e1 >= 0) {
                int n1 = a.at(e1)- 48;
                int n = n1 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e1--;
            }
            else {
                int n2 = b.at(e2) - 48;
                int n = n2 + extra;
                rv.push_back(n % 2);
                extra = n / 2;
                e2--;
            }
        }
        if (extra > 0) {
            rv.push_back(extra);
        }
        string r = "";
        for (int j = rv.size() - 1; j >= 0; j--) {
           r += to_string(rv[j]);
        }
        return r;
    }
};