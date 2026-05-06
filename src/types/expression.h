#include <vector>
#include <memory>
#include <string>

#include "rational.h"
#include "variable.h"

#pragma once

enum OpType {
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV
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
	Expression(const Variable& x);

	std::string to_string() const;

	Expression& operator=(const Variable& x);
};