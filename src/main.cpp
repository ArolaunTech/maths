#include <iostream>

#include "ui/terminal.h"
#include "types/integer.h"
#include "types/rational.h"

int main() {
	Integer a = -500000000000;
	Integer b = -4300000000;

	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << a / b << "\n";
}