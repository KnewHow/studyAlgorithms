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
			// �ַ� s[right] ������target ��
			++window[s[right]];
		}
		// �����ǰ���ڵ��ַ�������Ŀ���ַ������Ƚ���С���ȣ�
		// �����ô��ڵ�left ��ǰ����
		while (check(window, target) && left <= right) {
			if (right - left + 1 < minLength) {
				minLength = right - left + 1;
				begin = left;
			}
			// ��� s[left] �� target �е��ַ����� window ���ٶ��ڴ���
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
	int counter = 0; // ��ǰ window ��ƥ��Ŀ���ַ����ĳ���
	while (right < s.size()) {
		++window[s[right]];
		if (target.find(s[right]) != target.end() &&
			target[s[right]] >= window[s[right]]) {
			// ֻ�е��ַ� s[right] ��target �д�����
			// С�ڵ���target�е��ַ�����ʱ��������Ϊ
			// ���ַ�����Ч��,����
			++counter;
		}
		// ��� couter �� size �ĳ�����ȣ���ʾ�����ҵ�����
		// ���ִ�����¼��С����
		while (counter == t.size() && left <= right) {
			int len = right - left + 1;
			if (len < minmunLen) {
				minmunLen = len;
				begin = left;
			}
			// ���ɹ�ƥ�������Ҫ��right��ʱ�������ƶ� left
		   // ȥ�ҽ϶̵��Ӵ�
			if (target.find(s[left]) != target.end() &&
				target[s[left]] >= window[s[left]]
				) {
				// �� s[left] �� target �е��ַ�����֮ǰ����¼��
				// ���ƶ� left ��ʱ����Ҫ�� counter--
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
	int counter = 0; // ��ǰ window ��ƥ��Ŀ���ַ����ĳ���
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
				// �� s[left] �� target �е��ַ�����֮ǰ����¼��
				// ���ƶ� left ��ʱ����Ҫ�� counter--
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
