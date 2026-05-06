#include <iostream>

#include "ui/terminal.h"
#include "types/all.h"

int main() {
	//Space s;

	//s.loadfile("test/space1.txt");

	Expression e;
	Variable x("x");

	e = x;

	std::cout << e.to_string() << "\n";
}