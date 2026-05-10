#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <limits>

#include "rational.h"
#include "variable.h"

#pragma once

enum OpType {
	OP_NULL,
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_POW,
	OP_LN,
	OP_LOG10,
	OP_LOG,
	OP_EXP,
	OP_SQRT
};

const std::unordered_map<OpType, int> oppriorities = {
	{OP_NULL, 0},
	{OP_ADD, 1},
	{OP_SUB, 1},
	{OP_MUL, 2},
	{OP_DIV, 2},
	{OP_POW, 3},
	{OP_LN, std::numeric_limits<int>::max()},
	{OP_LOG10, std::numeric_limits<int>::max()},
	{OP_LOG, std::numeric_limits<int>::max()},
	{OP_EXP, std::numeric_limits<int>::max()},
	{OP_SQRT, std::numeric_limits<int>::max()}
};

enum NodeType {
	NODE_EMPTY,
	NODE_RATIONAL,
	NODE_VARIABLE,
	NODE_OP
};

class Node {
public:
	virtual ~Node() {}

	virtual std::string to_string() const = 0;
	virtual NodeType gettype() const = 0;
};

class EmptyNode : public Node {
public:
	NodeType gettype() const override {return NODE_EMPTY;}

	std::string to_string() const override;
};

class RationalNode : public Node {
private:
	Rational val;
public:
	RationalNode(const Rational& x) : val(x) {}

	NodeType gettype() const override {return NODE_RATIONAL;}

	std::string to_string() const override;
};

class VariableNode : public Node {
private:
	Variable var;
public:
	VariableNode(const Variable& x) : var(x) {}

	NodeType gettype() const override {return NODE_VARIABLE;}

	std::string to_string() const override;
};

class OpNode : public Node {
private:
	OpType op;
public:
	OpNode(const OpType& newop) : op(newop) {}

	NodeType gettype() const override {return NODE_OP;}

	OpType getoptype() const {return op;}

	std::string to_string() const override;
};

class Expression {
private:
	std::shared_ptr<Node> data;
	std::vector<std::shared_ptr<Expression> > children;
public:
	Expression();
	Expression(const Integer& x);
	Expression(const Rational& x);
	Expression(const Variable& x);

	NodeType gettype() const;
	OpType getoptype() const;

	std::string to_string() const;

	Expression& operator+=(Expression const & rhs);
	Expression& operator-=(Expression const & rhs);
	Expression& operator*=(Expression const & rhs);
	Expression& operator/=(Expression const & rhs);

	Expression& operator=(const Integer& x);
	Expression& operator=(const Rational& x);
	Expression& operator=(const Variable& x);
};

Expression operator+(Expression const & lhs, Expression const & rhs);
Expression operator-(Expression const & lhs, Expression const & rhs);
Expression operator*(Expression const & lhs, Expression const & rhs);
Expression operator/(Expression const & lhs, Expression const & rhs);