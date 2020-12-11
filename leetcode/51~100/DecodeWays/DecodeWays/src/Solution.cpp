#include "Solution.h"

int Solution::numDecodings(std::string s)
{
	std::unordered_map<std::string, int> dp;
	int res = doDecoding(s, dp);
	return res;
}

int Solution::doDecoding(const std::string& s, std::unordered_map<std::string, int>& dp)
{
	if (dp.find(s) != dp.end()) {
		return dp.at(s);
	}
	else {
		if (s.empty()) {
			return 1;
		}
		else if (s[0] == '0') { // 开头是0的不能解码
			return 0;
		}
		else if (s.size() == 1) {
			dp.insert({ s,1 });
			return 1;
		}
		else { // s.size() >= 2
			int r = doDecoding(s.substr(1), dp); // 将第一位编码，递归剩下的字串
			std::string s1 = s.substr(0, 2);
			int nums = std::stoi(s1);
			if (nums >= 1 && nums <= 26) {
				r += doDecoding(s.substr(2), dp);
			}
			dp.insert({ s,r });
			return r;
		}
	}	
}

