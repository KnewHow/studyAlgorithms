#include<vector>
#include<string>
using namespace std;

class Solution {
public:
    
    string getPermutation(int n, int k) {
        vector<int> nums = vector<int>();
        vector<int> factorials = vector<int>();
        factorials.push_back(1);
        for (int i = 1; i < n; i++) {
            int v = factorials.at(i - 1) * i;
            factorials.push_back(v);
        }
        for (int i = 1; i <= n; i++) {
            nums.push_back(i);
        }
        k--;
        string r = "";
        for (int i = n - 1; i >= 0; i--) {
            int idx = k / factorials.at(i);
            k -= idx * factorials.at(i);
            r += to_string(nums.at(idx));
            nums.erase(nums.begin() + idx);
        }
        return r;
    }
};