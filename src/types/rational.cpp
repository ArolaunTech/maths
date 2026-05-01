#include <stdexcept>
#include <iostream>

#include "rational.h"

Rational::Rational(std::int64_t n) {
	Integer newn = n;

	num = newn;
	den = 1;
}

Rational::Rational(Integer n) {
	num = n;
	den = 1;
}

Rational::Rational(Integer n, Integer d) {
	if (d.iszero()) {
		throw std::invalid_argument("Fraction with zero denominator!");
	}

	num = n;
	den = d;

	simplify();
}

void Rational::simplify() {
	if (den.isnegative()) {
		num = -num;
		den = -den;
	}

	Integer factor = gcd(num, den);

	num /= factor;
	den /= factor;
}

Rational Rational::operator+(Rational const & rhs) const {
	Rational out(*this);

	out += rhs;

	return out;
}

Rational Rational::operator+() const {
	return *this;
}

Rational& Rational::operator+=(Rational const & rhs) {
	Integer oldden = den;

	num *= rhs.getDen();
	den *= rhs.getDen();

	num += rhs.getNum() * oldden;

	simplify();

	return *this;
}

Rational& Rational::operator++() {
	*this += 1;

	return *this;
}

Rational Rational::operator++(int) {
	Rational out(*this);

	*this += 1;

	return out;
}

Rational Rational::operator-(Rational const & rhs) const {
	return *this + (-rhs);
}

Rational Rational::operator-() const {
	Rational out(-num, den);

	return out;
}

Rational& Rational::operator-=(Rational const & rhs) {
	*this = *this - rhs;

	return *this;
}

Rational& Rational::operator--() {
	*this -= 1;

	return *this;
}

Rational Rational::operator--(int) {
	Rational out(*this);

	*this -= 1;

	return out;
}

Rational Rational::operator*(Rational const & rhs) const {
	Rational out(*this);

	out *= rhs;

	return out;
}

Rational& Rational::operator*=(Rational const & rhs) {
	num *= rhs.getNum();
	den *= rhs.getDen();

	simplify();

	return *this;
}

Rational Rational::operator/(Rational const & rhs) const {
	Rational out(*this);

	out /= rhs;

	return out;
}

Rational& Rational::operator/=(Rational const & rhs) {
	num *= rhs.getDen();
	den *= rhs.getNum();

	simplify();

	return *this;
}

bool Rational::operator==(Rational const & rhs) const {
	return num * rhs.getDen() == den * rhs.getNum();
}

bool Rational::operator!=(Rational const & rhs) const {
	return !(*this == rhs);
}

bool Rational::operator<(Rational const & rhs) const {
	if (den * rhs.getDen() > 0) {
		return num * rhs.getDen() < den * rhs.getNum();
	}
	return num * rhs.getDen() > den * rhs.getNum();
}

bool Rational::operator<=(Rational const & rhs) const {
	return (*this == rhs) || (*this < rhs);
}

bool Rational::operator>(Rational const & rhs) const {
	return !(*this <= rhs);
}

bool Rational::operator>=(Rational const & rhs) const {
	return !(*this < rhs);
}

Integer Rational::getNum() const {
	return num;
}

Integer Rational::getDen() const {
	return den;
}

std::string Rational::to_string() const {
	if (den == 1) return num.to_string();

	return num.to_string() + "/" + den.to_string();
}

std::ostream& operator<<(std::ostream& out, const Rational& x) {
	out << x.to_string();

	return out;
}