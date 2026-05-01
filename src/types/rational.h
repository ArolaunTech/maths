#include <string>
#include <cstdint>

#include "integer.h"

#pragma once

class Rational {
private:
	Integer num;
	Integer den;

	void simplify();
public:
	Rational(std::int64_t n);
	Rational(Integer n);
	Rational(Integer n, Integer d);

	Rational operator+(Rational const & rhs) const;
	Rational operator+() const;
	Rational& operator+=(Rational const & rhs);
	Rational& operator++();
	Rational operator++(int);

	Rational operator-(Rational const & rhs) const;
	Rational operator-() const;
	Rational& operator-=(Rational const & rhs);
	Rational& operator--();
	Rational operator--(int);

	Rational operator*(Rational const & rhs) const;
	Rational& operator*=(Rational const & rhs);
	Rational operator/(Rational const & rhs) const;
	Rational& operator/=(Rational const & rhs);

	bool operator==(Rational const & rhs) const;
	bool operator!=(Rational const & rhs) const;
	bool operator<(Rational const & rhs) const;
	bool operator<=(Rational const & rhs) const;
	bool operator>(Rational const & rhs) const;
	bool operator>=(Rational const & rhs) const;

	Integer getNum() const;
	Integer getDen() const;
	std::string to_string() const;
};

std::ostream& operator<<(std::ostream& out, const Rational& x);