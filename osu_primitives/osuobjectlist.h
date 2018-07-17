#ifndef OSUOBJECTLIST_H
#define OSUOBJECTLIST_H

class OsuObjectList {
public:

    virtual ~OsuObjectList();

    virtual QList<double> offsetList() const = 0;

    virtual int size() const = 0;
    virtual void sort(bool isAscending = true) = 0;
    virtual double length() const = 0;
    // virtual iterator impl

    // will need any_iter

};
#endif // OSUOBJECTLIST_H
