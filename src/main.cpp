#include <iostream>

#include "ui/terminal.h"
#include "types/all.h"

int main() {
	//Space s;

	//s.loadfile("test/space1.txt");

	Expression e, e2, e3;
	Variable x("x");
	Integer five = 5, six = 6;

	e = x;
	e2 = five;

	e3 = e * e2 / six;

	std::cout << e.to_string() << "\n";
	std::cout << e2.to_string() << "\n";
	std::cout << e3.to_string() << "\n";
}