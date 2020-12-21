#include "Solution.h"


std::vector<std::string> Solution::restoreIpAddresses(std::string s)
{
	std::vector<std::string> res;
	std::vector<std::string> temp;
	doParse(s, res, temp, 0, 0);
	return res;
}

void Solution::doParse(const std::string& s, std::vector<std::string>& res, std::vector<std::string>& temp, int currentSegment, int startIndex)
{
	if (currentSegment == SEGMENT_TOTAL) { // �����ĸ�IP�β����ַ���Ҳ�պ�����
		if (s.size() == startIndex) {
			std::string address;
			for (int i = 0; i < SEGMENT_TOTAL; i++) {
				address += temp[i];
				if (i != SEGMENT_TOTAL - 1) {
					address += '.';
				}
			}
			res.push_back(address);
		}
		return;
	}
	else { // ��û�������ĸ�IP��
		if (startIndex == s.size()) {
			return;
		}
		if (s[startIndex] == '0') { // �����ǰ�ַ�Ϊ0��ֻ������������Ϊһ��
			temp.push_back(s.substr(startIndex, 1));
			doParse(s, res, temp, currentSegment + 1, startIndex + 1);
			temp.pop_back();
		}
		else {
			int currentValue = 0;
			for (int i = startIndex; i < s.size(); i++) {
				currentValue = currentValue * 10 + (s[i] - '0');
				if (currentValue >= 0 && currentValue <= 0xFF) {
					std::string t = s.substr(startIndex, i - startIndex + 1);
					temp.push_back(t);
					doParse(s, res, temp, currentSegment + 1, i + 1);
					temp.pop_back();
				}
				else {
					break;
				}
			}
		}
	}
}
