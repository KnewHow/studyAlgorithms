#include "Solution.h"

bool Solution::isScramble(std::string s1, std::string s2)
{
	std::unordered_map<std::string, int> dp;
	return doScramble(s1, s2, dp);
}

bool Solution::doScramble(std::string s1, std::string s2, std::unordered_map<std::string, int> dp)
{
	int r = dp.find(s1) == dp.end() ? -1 : dp.at(s1);
	if (r == 0) {
		return false;
	}
	else if (r == 1) {
		return true;
	}
	else {
		if (s1.size() != s2.size()) {
			std::string s = s1 + "#" + s2;
			dp.insert({ s, 0 });
			return false;
		}
		if (s1 == s2) {
			std::string s = s1 + "#" + s2;
			dp.insert({ s, 1 });
			return true;
		}

		// check appera times
		std::vector<int> v(26, 0);
		for (int i = 0; i < s1.size(); i++) {
			int s1_char_to_index = s1[i] - 'a';
			int s2_char_to_index = s2[i] - 'a';
			v[s1_char_to_index]++;
			v[s2_char_to_index]--;
		}
		for (auto time : v) {
			if (time != 0) {
				std::string s = s1 + "#" + s2;
				dp.insert({ s, 0 });
				return false;
			}
		}

		for (int i = 1; i < s1.size(); i++) {
			if (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
				isScramble(s1.substr(i), s2.substr(i))) {
				std::string s = s1 + "#" + s2;
				dp.insert({ s, 1 });
				return true;
			}

			if (isScramble(s1.substr(i), s2.substr(0, s2.size() - i)) &&
				isScramble(s1.substr(0, i), s2.substr(s2.size() - i))) {
				std::string s = s1 + "#" + s2;
				dp.insert({ s, 1 });
				return true;
			}
		}
		std::string s = s1 + "#" + s2;
		dp.insert({ s, 0 });
		return false;
	}
}

bool Solution::isScramble2(std::string s1, std::string s2)
{
	if (s1.size() != s2.size()) {
		return false;
	}
	if (s1 == s2) {
		return true;
	}
	
	// check appera times
	std::vector<int> v(26, 0);
	for (int i = 0; i < s1.size(); i++) {
		int s1_char_to_index = s1[i] - 'a';
		int s2_char_to_index = s2[i] - 'a';
		v[s1_char_to_index]++;
		v[s2_char_to_index]--;
	}
	for (auto time : v) {
		if (time != 0) {
			return false;
		}
	}

	for (int i = 1; i < s1.size(); i++) {
		if (isScramble(s1.substr(0, i), s2.substr(0, i)) &&
			isScramble(s1.substr(i), s2.substr(i))) {
			return true;
		}

		if (isScramble(s1.substr(i), s2.substr(0, s2.size() - i)) &&
			isScramble(s1.substr(0, i), s2.substr(s2.size() - i))) {
			return true;
		}
	}
	return false;
}
