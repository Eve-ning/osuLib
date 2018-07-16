#include "osuobject.h"

OsuObject::~OsuObject() {

}

double OsuObject::offset() const
{
    return m_offset;
}

void OsuObject::setOffset(const double &offset)
{
    m_offset = offset;
}
