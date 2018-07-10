#ifndef BOUNDEDDOUBLE_H
#define BOUNDEDDOUBLE_H
#include <QtCore>

class BoundedDouble
{
public:
    explicit BoundedDouble(const int &value = 0,
                        const int &min = std::numeric_limits<int>::min(),
                        const int &max = std::numeric_limits<int>::max()) :
                        m_value(value), m_min(min), m_max(max){
        setValue(value);
    }

    BoundedDouble operator =(const int &value){
        // This clamps value, inclusive of boundaries.
        setValue(value);
        return *this;
    }

    explicit operator int() const {
        return int(m_value);
    }

    operator double() const {
        return int(m_value);
    }

    void setValue(const double &value){
        m_value = value < m_min ? m_min : (value > m_max ? m_max : value);
    }

    double value() const {
        return m_value < m_min ? m_min : (value > m_max ? m_max : value);
    }

    double hiddenValue() const {
        return m_value;
    }
    void forceClamp() const {
        m_value = m_value < m_min ? m_min : (value > m_max ? m_max : value);
    }

    BoundedDouble& operator +=(const double &value){
        setValue(m_value + value);
        return *this;
    }
    BoundedDouble& operator -=(const double &value){
        setValue(m_value - value);
        return *this;
    }
    BoundedDouble& operator *=(const double &value){
        setValue(m_value * value);
        return *this;
    }
    BoundedDouble& operator /=(const double &value){
        setValue(m_value / value);
        return *this;
    }

private:
    double m_value;
    double m_min;
    double m_max;
};


#endif // BOUNDEDDOUBLE_H
