#include <vector>
#include <cstdint>
#include <string>

#pragma once

class Integer {
private:
	bool negative;

	std::vector<std::uint32_t> digits;

	void div10();
	void flip();
	int lastdigit() const;
	void trim();
public:
	// Constructors
	Integer();
	Integer(std::int64_t val);

	// Utils
	std::uint32_t getNthdigit(int N) const;
	std::size_t getNumdigits() const;

	bool isnegative() const;
	bool iszero() const;

	void logdigits() const;

	void leftshift(int n);
	void rightshift(int n);

	std::string to_string() const;

	// Operators
	Integer operator+(Integer const & rhs) const;
	Integer operator+() const;
	Integer& operator+=(Integer const & rhs);
	Integer& operator++();
	Integer operator++(int);

	Integer operator-(Integer const & rhs) const;
	Integer operator-() const;
	Integer& operator-=(Integer const & rhs);
	Integer& operator--();
	Integer operator--(int);

	Integer operator*(Integer const & rhs) const;
	Integer& operator*=(Integer const & rhs);
	Integer operator/(Integer const & rhs) const;
	Integer& operator/=(Integer const & rhs);
	//TODO: division + modulo

	Integer operator<<(std::size_t pos) const;
	Integer& operator<<=(std::size_t pos);
	Integer operator>>(std::size_t pos) const;
	Integer& operator>>=(std::size_t pos);

	bool operator==(Integer const & rhs) const;
	bool operator<(Integer const & rhs) const;
	bool operator<=(Integer const & rhs) const;
	bool operator>(Integer const & rhs) const;
	bool operator>=(Integer const & rhs) const;
	bool operator!() const;
};

std::ostream& operator<<(std::ostream& out, const Integer& n);

Integer abs(Integer x);
Integer gcd(Integer a, Integer b);