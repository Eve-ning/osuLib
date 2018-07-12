#ifndef BOUNDEDINT_H
#define BOUNDEDINT_H
#include <QtCore>

class BoundedInt
{
public:
    explicit BoundedInt(const int &value = 0,
                        const int &min = std::numeric_limits<int>::min(),
                        const int &max = std::numeric_limits<int>::max()) :
                        m_value(value), m_min(min), m_max(max){
        setValue(value);
    }

    BoundedInt& operator =(const int &value){
        setValue(value);
        return *this;
    }

    operator int() const {
        return value();
    }

    explicit operator double() const {
        return double(value());
    }

    void setValue(const int &value){
        m_value = value;
    }

    int value() const {
        // This clamps value, inclusive of boundaries.
        return (m_value < m_min ? m_min : (m_value > m_max ? m_max : m_value));
    }

    int hiddenValue() const {
        return m_value;
    }
    void forceClamp() {
        m_value = (m_value < m_min ? m_min : (m_value > m_max ? m_max : m_value));
    }

    BoundedInt& operator +=(const int &value){
        setValue(m_value + value);
        return *this;
    }
    BoundedInt& operator -=(const int &value){
        setValue(m_value - value);
        return *this;
    }
    BoundedInt& operator *=(const int &value){
        setValue(m_value * value);
        return *this;
    }
    BoundedInt& operator /=(const int &value){
        setValue(m_value / value);
        return *this;
    }

private:
    int m_value;
    int m_min;
    int m_max;
};

#endif // BOUNDEDINT_H
