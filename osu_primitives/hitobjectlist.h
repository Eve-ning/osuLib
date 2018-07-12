#ifndef HITOBJECTLIST_H
#define HITOBJECTLIST_H
#include "hitobject.h"

class HitObjectList
{
public:
    HitObjectList();

private:
    QList<HitObject> m_value = {};

};

#endif // HITOBJECTLIST_H
