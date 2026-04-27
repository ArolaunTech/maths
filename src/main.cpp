#include <iostream>

#include "ui/terminal.h"
#include "types/integer.h"
#include "types/rational.h"

int main() {
	Integer a = 7;
	Integer b = 2;

	std::cout << a << "\n";
	//std::cout << (a / b).to_string() << "\n";
	std::cout << (a << 65) << "\n";
}