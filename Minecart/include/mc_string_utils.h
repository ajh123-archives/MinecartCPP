#ifndef MINECART_STRING_UTILS_H
#define MINECART_STRING_UTILS_H

#include <numeric>
#include <string>
#include <sstream>
#include <vector>

namespace minecart {
	namespace utils {
		std::string JoinStringVector(std::string delimiter, std::vector<std::string> vector);
		std::vector<std::string> SplitStringToVector(char delimiter, std::string input);
	}
}

#endif // MINECART_STRING_UTILS_H
