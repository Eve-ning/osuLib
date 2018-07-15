#ifndef DBUG_H
#define DBUG_H

#define DEBUGTITLE(title) qDebug() << "[ -- " << title << " TEST -- ]"
#define DEBUGPASS(title) qDebug() << "[ -- " << title << " TEST PASS -- ]"
#define DEBUGLABEL(title) qDebug() << "[ ## " << title << " ## ]"
#define DEBUGSEP qDebug() << endl << "- - - - - - - -" << endl

#include "primitives/bounded/boundedint.h"
#include "primitives/bounded/boundeddouble.h"
#include "osu_primitives/hitobjectlist.h"
#include "osu_primitives/timingpointlist.h"
#include "osu_algorithms/osualgorithm.h"
#include <QDebug>



class Dbug
{
public:
    Dbug();

    static void primitive_debug() {
        DEBUGTITLE("Debug");

        DEBUGTITLE("BoundedInt");
        if (debug_boundedInt()) { DEBUGPASS("BoundedInt"); }
        DEBUGSEP;

        DEBUGTITLE("BoundedDouble");
        if (debug_boundedDouble()) { DEBUGPASS("BoundedDouble"); }
        DEBUGSEP;

        DEBUGTITLE("HitObject");
        if (debug_hitObject()) { DEBUGPASS("HitObject"); }
        DEBUGSEP;

        DEBUGTITLE("TimingPoint");
        if (debug_timingPoint()) { DEBUGPASS("TimingPoint"); }
        DEBUGSEP;

        DEBUGTITLE("HitObjectList");
        if (debug_hitObjectList()) { DEBUGPASS("HitObjectList"); }
        DEBUGSEP;

        DEBUGTITLE("TimingPointList");
        if (debug_timingPointList()) { DEBUGPASS("TimingPointList"); }
        DEBUGSEP;

        DEBUGPASS("Debug");
    }
    static void algorithm_debug() {
        DEBUGTITLE("Debug");

        DEBUGTITLE("countInRange");
        if (debug_countInRange()) { DEBUGPASS("countInRange"); }
        DEBUGSEP;

        DEBUGTITLE("adjustToAverage");
        if (debug_adjustToAverage()) { DEBUGPASS("adjustToAverage"); }
        DEBUGSEP;

        DEBUGPASS("Debug");
    }

private:

    static bool debug_boundedInt();
    static bool debug_boundedDouble();
    static bool debug_hitObject();
    static bool debug_timingPoint();
    static bool debug_hitObjectList();
    static bool debug_timingPointList();

    static bool debug_countInRange();
    static bool debug_adjustToAverage();

    static bool compareDebug(const double &expected,
                             const double &given);
    static bool compareDebug(const QString &expected,
                             const QString &given);
    static bool compareDebug(const QStringList &expected,
                             const QStringList &given);

    static TimingPointList getEgTP();
    static HitObjectList getEgHO();

private:

};

#endif // DBUG_H
