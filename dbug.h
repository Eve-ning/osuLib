#ifndef DBUG_H
#define DBUG_H

#define DEBUGTITLE(title) qDebug() << "[ -- " << title << " TEST -- ]"
#define DEBUGPASS(title) qDebug() << "[ -- " << title << " TEST PASS -- ]"
#define DEBUGSEP qDebug() << endl << "- - - - - - - -" << endl

#include "primitives/bounded/boundedint.h"
#include "primitives/bounded/boundeddouble.h"
#include "osu_primitives/hitobjectlist.h"
#include "osu_primitives/timingpointlist.h"
#include <QDebug>

class Dbug
{
public:
    Dbug();

    static void full_debug() {
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

private:

    static bool debug_boundedInt();
    static bool debug_boundedDouble();
    static bool debug_hitObject();
    static bool debug_timingPoint();
    static bool debug_hitObjectList();
    static bool debug_timingPointList();

    static bool compareDebug(const double &expected,
                             const double &given);
    static bool compareDebug(const QString &expected,
                             const QString &given);
    static bool compareDebug(const QStringList &expected,
                             const QStringList &given);
};

#endif // DBUG_H
