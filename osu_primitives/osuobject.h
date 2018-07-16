#ifndef OSUOBJECT_H
#define OSUOBJECT_H

#include "primitives/bounded/boundedint.h"
#include "primitives/bounded/boundeddouble.h"
#include "primitives/sampleset.h"

class OsuObject {
public:

    virtual ~OsuObject();

    double offset() const;
    void setOffset(const double &offset);

protected:

    BoundedDouble m_offset = BoundedDouble(0, 0);

};

#endif // OSUOBJECT_H
