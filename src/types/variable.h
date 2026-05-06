#include <string>

#pragma once

class Variable {
private:
	std::string name;
public:
	Variable(std::string newname) : name(newname) {}

	std::string to_string() const;
};