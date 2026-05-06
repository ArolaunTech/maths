#include <iostream>
#include <stdexcept>

#include "expression.h"

Expression::Expression() {
	data = std::make_shared<EmptyNode>();
}

Expression::Expression(const Variable& x) {
	*this = x;
}

std::string Expression::to_string() const {
	if (data->gettype() == NODE_OP) {
		std::shared_ptr<OpNode> op = std::dynamic_pointer_cast<OpNode>(data);

		if (!op) return "";

		switch (op->getoptype()) {
		default:
			return "";
		}
	}

	return data->to_string();
}

Expression& Expression::operator=(const Variable& x) {
	Variable copy(x);
	data = std::make_shared<VariableNode>(copy);

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