#include <vector>
#include <string>
#include <iterator>

namespace h{
	std::vector<std::string> split(const std::string & str, const std::string & splitBy);
	std::vector<std::string> split(const std::string & str, const char splitBy);
};