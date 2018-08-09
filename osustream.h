#ifndef OSUSTREAM_H
#define OSUSTREAM_H
#include "osu_primitives/osuobjectlist.h"

// Osu Stream helps output OsuObjects and modify output

template <class ObjType>
class OsuStream
{
public:
    OsuStream(std::shared_ptr<OsuObjectList<ObjType>> value) : objList(value){}



private:
    std::shared_ptr<OsuObjectList<ObjType>> objList;
};

#endif // OSUSTREAM_H
