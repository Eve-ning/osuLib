#ifndef DBUG_H
#define DBUG_H

#include "primitives/bounded/boundedint.h"
#include "primitives/bounded/boundeddouble.h"
#include "osu_primitives/hitobject.h"
#include "osu_primitives/timingpoint.h"
#include <QDebug>

class Dbug
{
public:
    Dbug();

    static void full_debug() {
        qDebug() << "[Debug]";

        if (debug_boundedInt()) { qDebug() << "BoundedInt Pass."; }
        qDebug() << "--";
        if (debug_boundedDouble()) { qDebug() << "BoundedDouble Pass."; }
        qDebug() << "--";
        if (debug_hitObject()) { qDebug() << "HitObject Pass."; }
        qDebug() << "--";
        if (debug_timingPoint()) { qDebug() << "TimingPoint Pass."; }
        qDebug() << "--";
    }

private:

    static bool debug_boundedInt();
    static bool debug_boundedDouble();
    static bool debug_hitObject();
    static bool debug_timingPoint();

    static bool compareDebug(const double &expected,
                             const double &given);
    static bool compareDebug(const QString &expected,
                             const QString &given);
};

#endif // DBUG_H
