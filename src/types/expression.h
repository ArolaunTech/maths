#include <vector>
#include <memory>

#include "rational.h"

#pragma once

enum OpType {
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV
};

enum NodeType {
	NODE_RATIONAL,
	NODE_VARIABLE,
	NODE_OP
};

class Node {
private:
	std::vector<std::shared_ptr<Node> > children;
public:
	virtual ~Node() {}
};

class RationalNode : public Node {
private:
	Rational val;
public:
	RationalNode(const Rational& x) : val(x) {}

	NodeType gettype() const {return NODE_RATIONAL;}
};

class VariableNode : public Node {
private:
	int id;
public:
	VariableNode(int x) : id(x) {}

	NodeType gettype() const {return NODE_VARIABLE;}
};

class OpNode : public Node {
private:
	OpType op;
public:
	OpNode(const OpType& newop) : op(newop) {}

	NodeType gettype() const {return NODE_OP;}
};

class Expression {
private:
	Node tree;
public:
	Expression() {}
};