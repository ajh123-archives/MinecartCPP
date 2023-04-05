#include "mc_string_utils.h"

std::string minecart::utils::JoinStringVector(std::string delimiter, std::vector<std::string> vector) {
	std::string result = std::accumulate(vector.begin(), vector.end(), std::string(),
		[&](const std::string& a, const std::string& b) {
		return a.empty() ? b : a + delimiter + b;
	});
	return result;
}

std::vector<std::string> minecart::utils::SplitStringToVector(char delimiter, std::string input) {
	std::vector<std::string> vec;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		vec.push_back(token);
	}

	return vec;
}
