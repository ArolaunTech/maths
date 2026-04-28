#include <iostream>

#include "ui/terminal.h"
#include "types/integer.h"
#include "types/rational.h"

int main() {
	Integer a = 1071;
	Integer b = 462;

	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << gcd(a, b) << "\n";
}