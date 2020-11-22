#include "Solution.h"

std::string Solution::simplifyPath(std::string path)
{
	std::stringstream is(path);
	std::vector<std::string> pathName;
	std::string tmp;
	while (std::getline(is, tmp, '/')) {
		if (tmp == "" || tmp == ".") {
			continue;
		}
		else if (tmp == ".." && !pathName.empty()) {
			pathName.pop_back();
		}
		else if (tmp != "..") {
			pathName.push_back(tmp);
		}	
	}

	if (pathName.empty()) {
		return "/";
	}
	else {
		std::string result = "";
		for (std::string name : pathName) {
			result += "/" + name;
		}
		return result;
	}
}

