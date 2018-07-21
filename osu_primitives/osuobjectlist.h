#ifndef OSUOBJECTLIST_H
#define OSUOBJECTLIST_H
#include "osuobject.h"

template <class ObjType>
class OsuObjectList {
public:

    virtual ~OsuObjectList(){}

    virtual QList<double> offsetList() const = 0;
    virtual void setOffsetList (const QList<double> &value) = 0;

    virtual typename std::shared_ptr<ObjType> operator [](int i) const = 0;
    virtual typename std::shared_ptr<ObjType> at(int i) const = 0;

    virtual double min() const = 0;
    virtual double max() const = 0;

    virtual int size() const = 0;
    virtual void sort(bool isAscending = true) = 0;
    virtual double length() const = 0;

    virtual typename QList<std::shared_ptr<ObjType>>::const_iterator begin() const { return m_value.begin(); }
    virtual typename QList<std::shared_ptr<ObjType>>::const_iterator end() const { return m_value.end(); }
protected:

    QList<std::shared_ptr<ObjType>> m_value = {};
};
#endif // OSUOBJECTLIST_H
