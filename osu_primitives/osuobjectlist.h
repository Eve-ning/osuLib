#ifndef OSUOBJECTLIST_H
#define OSUOBJECTLIST_H
#include "osuobject.h"

template <class ObjType>
class OsuObjectList {
public:

    OsuObjectList() : m_value(){}
    OsuObjectList(const OsuObjectList&) = default;
    OsuObjectList(OsuObjectList&&) = default;
    OsuObjectList& operator=(const OsuObjectList&) & = default;
    OsuObjectList& operator=(OsuObjectList&&) & = default;

    OsuObjectList(QList<std::shared_ptr<ObjType>> value) : m_value(value){}

    virtual ~OsuObjectList(){}

    std::shared_ptr<OsuObjectList> clone() const { return doClone(); }

    virtual QList<double> offsetList() const {
        QList<double> output = {};
        for (std::shared_ptr<ObjType> TP : m_value) { output.append(TP->offset()); }
        return output;
    }
    virtual void setOffsetList (const QList<double> &value) {
        if (!sameSize(value)) {
            return;
        }
        for (int i = 0; i < size(); ++i) {
            m_value[i]->setOffset(value[i]);
        }
    }

    virtual typename std::shared_ptr<ObjType> operator [](int i) const { return at(i); }
    virtual typename std::shared_ptr<ObjType> at(int i) const {
        if (i < size() && i >= 0) {
            return m_value.at(i);
        } else {
            qDebug() << "Index on TimingPointList out of range.";
            return m_value.at(0);
        }
    }

    virtual double min() const {
        auto offset_list = offsetList();
        return *std::min_element(offset_list.begin(), offset_list.end());
    }
    virtual double max() const {
        auto offset_list = offsetList();
        return *std::min_element(offset_list.begin(), offset_list.end());
    }

    virtual int size() const {
        return m_value.size();
    }
    virtual void sort(bool isAscending = true) {
        std::sort(m_value.begin(), m_value.end(),
                  [isAscending](std::shared_ptr<ObjType> a,
                                std::shared_ptr<ObjType> b){
            if (isAscending) {
                return a->offset() < b->offset();
            } else {
                return a->offset() > b->offset();
            }
        });
    }
    virtual double length() const {
        return max() - min();
    }

    virtual QList<std::shared_ptr<ObjType>> value() const { return m_value; }
    virtual void setValue(const QList<std::shared_ptr<ObjType>> &value) { m_value = value; }

    virtual typename QList<std::shared_ptr<ObjType>>::const_iterator begin() const { return m_value.begin(); }
    virtual typename QList<std::shared_ptr<ObjType>>::const_iterator end() const { return m_value.end(); }

protected:

    QList<std::shared_ptr<ObjType>> m_value = {};

    template <typename T>
    bool sameSize(QList<T> compare){
        return this->size() == compare.size();
    }

    virtual std::shared_ptr<OsuObjectList> doClone() const {
        QList<std::shared_ptr<ObjType>> output;
        output = std::move(m_value);
        return std::make_shared<OsuObjectList>(m_value);
    }
};



#endif // OSUOBJECTLIST_H
