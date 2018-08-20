#pragma once

#include <limits>

class BoundedDouble
{
public:
	explicit BoundedDouble(const double &value = 0,
		const double &min = std::numeric_limits<double>::lowest(),
		const double &max = std::numeric_limits<double>::max()) :
		m_value(value), m_min(min), m_max(max) {
		setValue(value);
	}

	BoundedDouble operator =(const double &value) {

		setValue(value);
		return *this;
	}

	explicit operator int() const {
		return int(value());
	}

	operator double() const {
		return value();
	}

	void setValue(const double &value) {
		m_value = value;
	}

	double value() const {
		// This clamps value, inclusive of boundaries.
		return (m_value < m_min ? m_min : (m_value > m_max ? m_max : m_value));
	}

	double hiddenValue() const {
		return m_value;
	}
	void forceClamp() {
		m_value = (m_value < m_min ? m_min : (m_value > m_max ? m_max : m_value));
	}

	BoundedDouble& operator +=(const double &value) {
		setValue(m_value + value);
		return *this;
	}
	BoundedDouble& operator -=(const double &value) {
		setValue(m_value - value);
		return *this;
	}
	BoundedDouble& operator *=(const double &value) {
		setValue(m_value * value);
		return *this;
	}
	BoundedDouble& operator /=(const double &value) {
		setValue(m_value / value);
		return *this;
	}

private:
	double m_value;
	double m_min;
	double m_max;
};

