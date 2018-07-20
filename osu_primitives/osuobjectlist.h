#ifndef OSUOBJECTLIST_H
#define OSUOBJECTLIST_H
#include "osuobject.h"

class OsuObjectList {
public:

    virtual ~OsuObjectList();

    virtual QList<double> offsetList() const = 0;

    virtual int size() const = 0;
    virtual void sort(bool isAscending = true) = 0;
    virtual double length() const = 0;
    // virtual iterator impl

    // will need any_iter

protected:

    QList<std::shared_ptr<OsuObject>> m_baseValue = {};

};
#endif // OSUOBJECTLIST_H
