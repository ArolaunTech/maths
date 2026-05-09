#include <iostream>
#include <stdexcept>

#include "expression.h"

Expression::Expression() {
	data = std::make_shared<EmptyNode>();
}

Expression::Expression(const Integer& x) {
	*this = x;
}

Expression::Expression(const Rational& x) {
	*this = x;
}

Expression::Expression(const Variable& x) {
	*this = x;
}

NodeType Expression::gettype() const {
	return data->gettype();
}

std::string Expression::to_string() const {
	if (data->gettype() == NODE_OP) {
		std::shared_ptr<OpNode> op = std::dynamic_pointer_cast<OpNode>(data);

		if (!op) return "";

		std::vector<std::string> childrenstrings;

		for (std::size_t i = 0; i < children.size(); i++) {
			childrenstrings.push_back(children[i]->to_string());
		}

		switch (op->getoptype()) {
		case OP_ADD:
			return childrenstrings[0] + " + " + childrenstrings[1];
		case OP_SUB:
			return childrenstrings[0] + " - " + childrenstrings[1];
		case OP_MUL:
			if (children[0]->gettype() == NODE_VARIABLE && children[1]->gettype() == NODE_RATIONAL) {
				return childrenstrings[1] + childrenstrings[0];
			}

			if (children[1]->gettype() == NODE_VARIABLE && children[0]->gettype() == NODE_RATIONAL) {
				return childrenstrings[0] + childrenstrings[1];
			}

			return "(" + childrenstrings[0] + ") * (" + childrenstrings[1] + ")";
		case OP_DIV:
			return "(" + childrenstrings[0] + ") / (" + childrenstrings[1] + ")";
		default:
			return "";
		}
	}

	return data->to_string();
}

Expression Expression::operator+(Expression const & rhs) const {
	Expression copy(*this);

	copy += rhs;

	return copy;
}

Expression& Expression::operator+=(Expression const & rhs) {
	std::vector<std::shared_ptr<Expression> > newchildren;

	newchildren.push_back(std::make_shared<Expression>(*this));
	newchildren.push_back(std::make_shared<Expression>(rhs));

	children = newchildren;

	data = std::make_shared<OpNode>(OP_ADD);

	return *this;
}

Expression Expression::operator-(Expression const & rhs) const {
	Expression copy(*this);

	copy -= rhs;

	return copy;
}

Expression& Expression::operator-=(Expression const & rhs) {
	std::vector<std::shared_ptr<Expression> > newchildren;

	newchildren.push_back(std::make_shared<Expression>(*this));
	newchildren.push_back(std::make_shared<Expression>(rhs));

	children = newchildren;

	data = std::make_shared<OpNode>(OP_SUB);

	return *this;
}

Expression Expression::operator*(Expression const & rhs) const {
	Expression copy(*this);

	copy *= rhs;

	return copy;
}

Expression& Expression::operator*=(Expression const & rhs) {
	std::vector<std::shared_ptr<Expression> > newchildren;

	newchildren.push_back(std::make_shared<Expression>(*this));
	newchildren.push_back(std::make_shared<Expression>(rhs));

	children = newchildren;

	data = std::make_shared<OpNode>(OP_MUL);

	return *this;
}

Expression Expression::operator/(Expression const & rhs) const {
	Expression copy(*this);

	copy /= rhs;

	return copy;
}

Expression& Expression::operator/=(Expression const & rhs) {
	std::vector<std::shared_ptr<Expression> > newchildren;

	newchildren.push_back(std::make_shared<Expression>(*this));
	newchildren.push_back(std::make_shared<Expression>(rhs));

	children = newchildren;

	data = std::make_shared<OpNode>(OP_DIV);

	return *this;
}

Expression& Expression::operator=(const Integer& x) {
	Rational copy(x, 1);
	data = std::make_shared<RationalNode>(copy);
	children.clear();

	return *this;
}

Expression& Expression::operator=(const Rational& x) {
	Rational copy(x);
	data = std::make_shared<RationalNode>(copy);
	children.clear();

	return *this;
}

Expression& Expression::operator=(const Variable& x) {
	Variable copy(x);
	data = std::make_shared<VariableNode>(copy);
	children.clear();

	return *this;
}

std::string EmptyNode::to_string() const {
	return "";
}

std::string RationalNode::to_string() const {
	return val.to_string();
}

std::string VariableNode::to_string() const {
	return var.to_string();
}

std::string OpNode::to_string() const {
	return "op";
}