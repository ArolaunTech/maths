#include <iostream>

#include "ui/terminal.h"
#include "types/integer.h"

int main() {
	Integer a = 30000000000, b = -40000000001;

	std::cout << "a = " << a.to_string() << ", b = " << b.to_string() << "\n";
	std::cout << "a - b = " << (a - b).to_string() << "\n";
}