#include <vector>

#include "expression.h"

#pragma once

class Statement {
};

enum EqualityType {
	INEQ_LESS,
	INEQ_LEQ,
	INEQ_GREATER,
	INEQ_GEQ
};

class Equality : public Statement {
private:
	EqualityType type;

	Expression lhs;
	Expression rhs;
public:
};

class VariableAssignment : public Statement {
private:
	int id;

	Expression value;
public:
};

class Space {
private:
	std::vector<Statement> statements;
public:

	void loadfile(char const * path);
};