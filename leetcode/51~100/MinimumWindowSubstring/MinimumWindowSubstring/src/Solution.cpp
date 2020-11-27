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

std::string Solution::minWindow2(std::string s, std::string t)
{
	std::unordered_map<char, int> target;
	std::unordered_map<char, int> window;

	for (const auto& c : t) {
		++target[c];
	}

	int left = 0, right = 0;
	int minmunLen = 1000000;
	int begin = -1;
	int counter = 0; // 当前 window 中匹配目标字符串的长度
	while (right < s.size()) {
		++window[s[right]];
		if (target.find(s[right]) != target.end() &&
			target[s[right]] >= window[s[right]]) {
			// 只有当字符 s[right] 在target 中存在且
			// 小于等于target中的字符数量时，我们认为
			// 该字符是有效的,自增
			++counter;
		}
		// 如果 couter 和 size 的长度相等，表示我们找到符合
		// 的字串，记录最小长度
		while (counter == t.size() && left <= right) {
			int len = right - left + 1;
			if (len < minmunLen) {
				minmunLen = len;
				begin = left;
			}
			// 当成功匹配后，我们要让right暂时不动，移动 left
		   // 去找较短的子串
			if (target.find(s[left]) != target.end() &&
				target[s[left]] >= window[s[left]]
				) {
				// 当 s[left] 是 target 中的字符，且之前被记录过
				// 在移动 left 的时候，需要将 counter--
				--counter;
			}
			--window[s[left]];
			left++;
		}
		right++;
	}

	return begin == -1 ? std::string() : s.substr(begin, minmunLen);
}

std::string Solution::minWindow3(std::string s, std::string t)
{
	int target[300] = { 0 };
	int window[300] = { 0 };
	
	for (const auto& c : t) {
		++target[c];
	}

	int left = 0, right = 0;
	int minmunLen = 1000000;
	int begin = -1;
	int counter = 0; // 当前 window 中匹配目标字符串的长度
	while (right < s.size()) {
		++window[s[right]];
		if (target[s[right]] != 0 &&
			target[s[right]] >= window[s[right]]) {
			
			++counter;
		}

		while (counter == t.size() && left <= right) {
			int len = right - left + 1;
			if (len < minmunLen) {
				minmunLen = len;
				begin = left;
			}
			if (target[s[left]] != 0 &&
				target[s[left]] >= window[s[left]]
				) {
				// 当 s[left] 是 target 中的字符，且之前被记录过
				// 在移动 left 的时候，需要将 counter--
				--counter;
			}
			--window[s[left]];
			left++;
		}
		right++;
	}

	return begin == -1 ? std::string() : s.substr(begin, minmunLen);
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
