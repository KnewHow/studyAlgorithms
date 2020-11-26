#include "Solution.h"

std::string Solution::minWindow(std::string s, std::string t)
{
	std::unordered_map<char, int> window;
	std::unordered_map<char, int> target;

	for (const auto& c : t) {
		++target[c];
	}

	int minLength = 1000000;
	int begin = -1;
	int left = 0;
	int right = -1;
	while (right < (int)s.size()) {
		if (target.find(s[++right]) != target.end()) {
			// 字符 s[right] 存在于target 中
			++window[s[right]];
		}
		// 如果当前窗口的字符串包含目标字符串，比较最小长度，
		// 并且让窗口的left 向前滑动
		while (check(window, target) && left <= right) {
			if (right - left + 1 < minLength) {
				minLength = right - left + 1;
				begin = left;
			}
			// 如果 s[left] 是 target 中的字符，让 window 减少对于次数
			if (target.find(s[left]) != target.end()) {
				--window[s[left]];
			}
			left++;
		}
	}
	return begin == -1 ? std::string() : s.substr(begin, minLength);
}

bool Solution::check(const std::unordered_map<char, int>& window, const std::unordered_map<char, int>& target)
{
	for (const std::pair<const char, int>& entry : target) {
		int a = 0;
		if (window.find(entry.first) != window.end()) {
			a = window.at(entry.first);
		}
		if (a < entry.second) {
			return false;
		}
	}
	return true;
}
