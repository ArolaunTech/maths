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

	std::string to_string() const;

	// Operators
	Integer operator+(Integer const & rhs) const;
	Integer operator+() const;
	Integer& operator+=(Integer const & rhs);
	Integer operator-(Integer const & rhs) const;
	Integer operator-() const;

	bool operator==(Integer const & rhs) const;
	bool operator<(Integer const & rhs) const;
	bool operator<=(Integer const & rhs) const;
	bool operator>(Integer const & rhs) const;
	bool operator>=(Integer const & rhs) const;
};

Integer abs(Integer x);