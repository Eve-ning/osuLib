#ifndef DBUG_H
#define DBUG_H

#define DEBUGTITLE(title) qDebug() << "[ -- " << title << " TEST -- ]"
#define DEBUGPASS(title) qDebug() << "[ -- " << title << " TEST PASS -- ]"
#define DEBUGSEP qDebug() << endl << "- - - - - - - -" << endl

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

        DEBUGPASS("Debug");

//        debug idea
//        QStringList input({"64,192,11528,1,0,0:0:0:0:",
//                          "448,192,11528,1,0,0:0:0:0:",
//                          "192,192,11700,1,0,0:0:0:0:",
//                          "448,192,11873,1,0,0:0:0:0:",
//                          "192,192,12045,1,0,0:0:0:0:"});

//        HitObjectList test = HitObjectList(input, 4);
//        QStringList output = test.toStringList(4);
//        qDebug() << output;

//        test[4]->debugInfo();


//        QStringList input_2({"494,344.827586206897,4,1,1,5,1,0",
//                             "55666,-100,4,1,1,5,0,1",
//                             "77045,-100,4,1,1,5,0,0",
//                             "121873,-100,4,1,1,5,0,1",
//                             "143942,-100,4,1,1,5,0,0",
//                             "188080,-100,4,1,1,5,0,1"});

//        TimingPointList test_2 = TimingPointList(input_2);
//        QStringList output_2 = test_2.toStringList();
//        qDebug() << output_2;

//        test_2[0]->debugInfo();
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
