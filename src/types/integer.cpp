#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "integer.h"

Integer::Integer() {
	negative = false;
	digits.clear();
	digits.push_back(0);
}

Integer::Integer(std::int64_t val) {
	negative = val < 0;

	std::int64_t absval = (val < 0) ? -val : val;

	digits.clear();
	digits.push_back(absval & 0xffffffff);

	if (absval >> 32) {
		digits.push_back(absval >> 32);
	}
}

std::string Integer::to_string() const {
	Integer copy(*this);

	if (iszero()) return "0";

	std::string out = "";

	while (!copy.iszero()) {
		out += std::to_string(copy.lastdigit());

		copy.div10();
	}

	std::reverse(out.begin(), out.end());

	if (negative) {
		return "-" + out;
	}

	return out;
}

int Integer::lastdigit() const {
	// 2 ^ (32n) mod 10 == (n == 0) ? 1 : 6

	int out = 0;

	for (std::size_t i = 0; i < digits.size(); i++) {
		out += ((i == 0) ? 1 : 6) * (digits[i] % 10);
		out %= 10;
	}

	return out;
}

void Integer::div10() {
	std::uint64_t r = 0, d;

	for (int i = (int)digits.size() - 1; i >= 0; i--) {
		d = (digits[i] + r * 0x100000000) / 10;
		r = (digits[i] + r * 0x100000000) % 10;

		digits[i] = d;
	}
}

bool Integer::iszero() const {
	for (const std::uint32_t& digit : digits) {
		if (digit != 0) return false;
	}

	return true;
}

/*===== Utils =====*/

std::uint32_t Integer::getNthdigit(int N) const {
	if (N >= digits.size()) return 0;

	return digits[N];
}

std::size_t Integer::getNumdigits() const {
	return digits.size();
}

void Integer::flip() {
	negative = !negative;
}

bool Integer::isnegative() const {
	return negative;
}

void Integer::logdigits() const {
	for (const std::uint32_t& digit : digits) {
		std::cout << digit << " ";
	}
	std::cout << "\n";
}

void Integer::leftshift(int n) {
	if (n < 0) {
		rightshift(-n);
		return;
	}

	for (int i = 0; i < n; i++) {
		digits.insert(digits.begin(), 0);
	}
}

void Integer::rightshift(int n) {
	if (n < 0) {
		leftshift(-n);
		return;
	}

	for (int i = 0; i < n; i++) {
		digits.erase(digits.begin());
	}
}

void Integer::trim() {
	while (digits.size() > 1 && digits.back() == 0) {
		digits.pop_back();
	}
}

/*===== Operators =====*/

Integer Integer::operator+(Integer const & rhs) const {
	Integer out(*this);

	out += rhs;

	return out;
}

Integer Integer::operator+() const {
	return *this;
}

Integer& Integer::operator+=(Integer const & rhs) {
	if (isnegative() == rhs.isnegative()) {
		// Add magnitudes
		bool carry = false;

		std::size_t maxsize = getNumdigits();
		if (rhs.getNumdigits() > maxsize) {
			maxsize = rhs.getNumdigits();
		}

		for (std::size_t i = 0; i < maxsize; i++) {
			if (i >= digits.size()) digits.push_back(0);

			std::uint64_t res = (std::uint64_t)digits[i] + rhs.getNthdigit(i) + carry;

			carry = res > 0x100000000;

			digits[i] = res & 0xffffffff;
		}

		digits.push_back(carry);
	} else {
		// Subtract magnitudes
		if (abs(rhs) > abs(*this)) {
			*this = rhs + *this;
			return *this;
		}

		bool borrow = false;

		std::size_t maxsize = getNumdigits();
		if (rhs.getNumdigits() > maxsize) {
			maxsize = rhs.getNumdigits();
		}

		for (std::size_t i = 0; i < maxsize; i++) {
			if (i >= digits.size()) digits.push_back(0);

			std::int64_t res = (std::int64_t)digits[i] - rhs.getNthdigit(i) - borrow;

			borrow = res < 0;

			if (res < 0) {
				res += 0x100000000;
			}

			digits[i] = res;
		}
	}

	trim();

	return *this;
}

Integer& Integer::operator++() {
	*this += 1;

	return *this;
}

Integer Integer::operator++(int) {
	Integer copy(*this);

	*this += 1;

	return copy;
}

Integer Integer::operator-(Integer const & rhs) const {
	return *this + (-rhs);
}

Integer Integer::operator-() const {
	Integer copy(*this);

	copy.flip();

	return copy;
}

Integer& Integer::operator-=(Integer const & rhs) {
	*this = *this - rhs;
	return *this;
}

Integer& Integer::operator--() {
	*this -= 1;

	return *this;
}

Integer Integer::operator--(int) {
	Integer copy(*this);

	*this -= 1;

	return copy;
}

Integer Integer::operator*(Integer const & rhs) const {
	Integer out(*this);

	out *= rhs;

	return out;
}

Integer& Integer::operator*=(Integer const & rhs) {
	if (rhs.isnegative()) flip();

	std::vector<std::uint64_t> newdigits(getNumdigits() + rhs.getNumdigits());

	for (std::size_t i = 0; i < getNumdigits(); i++) {
		for (std::size_t j = 0; j < rhs.getNumdigits(); j++) {
			std::uint64_t res = (std::uint64_t)getNthdigit(i) * rhs.getNthdigit(j);

			newdigits[i + j] += res & 0xffffffff;
			newdigits[i + j + 1] += res >> 32;
		}
	}

	std::uint64_t carry = 0;
	for (std::size_t i = 0; i < newdigits.size(); i++) {
		newdigits[i] += carry;

		carry = newdigits[i] >> 32;

		newdigits[i] &= 0xffffffff;
	}

	digits.clear();

	for (std::size_t i = 0; i < newdigits.size(); i++) {
		digits.push_back(newdigits[i]);
	}

	return *this;
}

Integer Integer::operator/(Integer const & rhs) const {
	Integer out(*this);

	out /= rhs;

	return out;
}

Integer& Integer::operator/=(Integer const & rhs) {
	if (rhs.iszero()) {
		throw std::invalid_argument("Division by zero!");
	}

	if (abs(rhs) > abs(*this)) {
		digits.clear();
		digits.push_back(0);

		return *this;
	}

	bool afternegative = isnegative() != rhs.isnegative();

	//Divide magnitudes
	std::size_t lhsdigits = getNumdigits();
	std::size_t rhsdigits = rhs.getNumdigits();

	if (isnegative()) flip();

	Integer rhscopy = abs(rhs);
	rhscopy.leftshift(lhsdigits);

	std::vector<std::uint32_t> newdigits(lhsdigits - rhsdigits + 1);

	for (int i = lhsdigits * 32 - 1; i >= 0; i--) {
		*this <<= 1;

		if (*this >= rhscopy) {
			*this -= rhscopy;

			newdigits[i / 32] |= 1 << (i % 32);
		}
	}

	digits = newdigits;

	trim();

	if (afternegative) flip();

	return *this;
}

Integer Integer::operator%(Integer const & rhs) const {
	Integer out(*this);

	out %= rhs;

	return out;
}

Integer& Integer::operator%=(Integer const & rhs) {
	*this -= rhs * (*this / rhs);

	return *this;
}

Integer Integer::operator<<(std::size_t pos) const {
	Integer out(*this);

	out <<= pos;

	return out;
}

Integer& Integer::operator<<=(std::size_t pos) {
	if (pos == 0) return *this;

	if (pos >= 32) {
		leftshift(pos / 32);
		*this <<= (pos % 32);

		return *this;
	}

	digits.push_back(0);

	for (int i = (int)getNumdigits() - 2; i >= 0; i--) {
		std::uint64_t res = (std::uint64_t)digits[i] << pos;

		digits[i + 1] += res >> 32;
		digits[i] = res & 0xffffffff;
	}

	trim();

	return *this;
}

Integer Integer::operator>>(std::size_t pos) const {
	Integer out(*this);

	out >>= pos;

	return out;
}

Integer& Integer::operator>>=(std::size_t pos) {
	if (pos == 0) return *this;

	if (pos >= 32) {
		rightshift(pos / 32);
		*this >>= (pos % 32);

		return *this;
	}

	std::uint32_t transfermask = 1 << pos;
	transfermask -= 1;

	for (std::size_t i = 0; i < getNumdigits(); i++) {
		if (i > 0) {
			digits[i - 1] += (digits[i] & transfermask) << (32 - pos);
		}

		digits[i] >>= pos;
	}

	return *this;
}

bool Integer::operator==(Integer const & rhs) const {
	if (iszero() && rhs.iszero()) return true;
	if (iszero() != rhs.iszero()) return false;

	// Neither is zero
	if (isnegative() != rhs.isnegative()) return false;

	// Compare magnitudes
	std::size_t maxsize = getNumdigits();
	if (rhs.getNumdigits() > maxsize) {
		maxsize = rhs.getNumdigits();
	}

	for (std::size_t i = 0; i < maxsize; i++) {
		if (getNthdigit(i) != rhs.getNthdigit(i)) return false;
	}

	return true;
}

bool Integer::operator!=(Integer const & rhs) const {
	return !(*this == rhs);
}

bool Integer::operator<(Integer const & rhs) const {
	if (*this == rhs) return false;

	// At most one is zero
	if (iszero()) return !rhs.isnegative(); // 0 < +, 0 > -
	if (rhs.iszero()) return isnegative(); // - < 0, + > 0
	// Neither are zero
	if (isnegative() && !rhs.isnegative()) return true; // - < +
	if (!isnegative() && rhs.isnegative()) return false; // + > -
	// Same sign, different magnitude
	if (isnegative() && rhs.isnegative()) return !(-(*this) < -rhs);
	// Both positive

	std::size_t maxsize = getNumdigits();
	if (rhs.getNumdigits() > maxsize) {
		maxsize = rhs.getNumdigits();
	}

	for (int i = (int)maxsize - 1; i >= 0; i--) {
		if (getNthdigit(i) < rhs.getNthdigit(i)) return true;
		if (getNthdigit(i) > rhs.getNthdigit(i)) return false;
	}

	// Should never happen
	std::cout << "Bug here! Line 248\n";
	return false;
}

bool Integer::operator<=(Integer const & rhs) const {
	return (*this) < rhs || (*this) == rhs;
}

bool Integer::operator>(Integer const & rhs) const {
	return !(*this <= rhs);
}

bool Integer::operator>=(Integer const & rhs) const {
	return !(*this < rhs);
}

bool Integer::operator!() const {
	return iszero();
}

std::ostream& operator<<(std::ostream& out, const Integer& n) {
	out << n.to_string();

	return out;
}

/*===== Math =====*/

Integer abs(const Integer& x) {
	if (x.isnegative()) return -x;
	return x;
}

Integer gcd(const Integer& a, const Integer& b) {
	if (a.isnegative() || b.isnegative()) return gcd(abs(a), abs(b));
	
	if (b == 0) return a;
	return gcd(b, a % b);
}

Integer lcm(const Integer& a, const Integer& b) {
	return a * b / gcd(a, b);
}