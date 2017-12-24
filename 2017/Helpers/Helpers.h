#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <queue>

namespace aoc{
	std::vector<std::string> split(const std::string & str, const std::string & splitBy);
	std::vector<std::string> split(const std::string & str, const char splitBy);
	int measureTimeMS();
	int measureTimeUS();
};