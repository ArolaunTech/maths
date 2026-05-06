#include <fstream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cctype>

#include "../types/statement.h"

bool iswhitespace(const std::string& s) {
	for (std::size_t i = 0; i < s.size(); i++) {
		if (std::isspace(s[i])) continue;
		return false;
	}
	return true;
}

void Space::loadfile(char const * path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::string eq;

	while (std::getline(file, eq)) {
		if (iswhitespace(eq)) continue;
		
		std::cout << eq << "\n";
	}

	file.close();
}