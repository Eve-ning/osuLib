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

    }

    BoundedInt operator =(const int &value){
        // This clamps value, inclusive of boundaries.
        return BoundedInt(value < m_min ? m_min : (value > m_max ? m_max : value));
    }

    operator int() const {
        return m_value;
    }

private:
    int m_value;
    int m_min;
    int m_max;
};

#endif // BOUNDEDINT_H
