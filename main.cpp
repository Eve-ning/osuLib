#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"
#include "osu_primitives/hitobjectlist.h"
#include "osu_primitives/timingpointlist.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dbug::full_debug();


    QStringList input({"64,192,11528,1,0,0:0:0:0:",
                      "448,192,11528,1,0,0:0:0:0:",
                      "192,192,11700,1,0,0:0:0:0:",
                      "448,192,11873,1,0,0:0:0:0:",
                      "192,192,12045,1,0,0:0:0:0:"});

    HitObjectList test = HitObjectList(input, 4);
    QStringList output = test.toStringList(4);
    qDebug() << output;

    test[4]->debugInfo();


    QStringList input_2({"494,344.827586206897,4,1,1,5,1,0",
                         "55666,-100,4,1,1,5,0,1",
                         "77045,-100,4,1,1,5,0,0",
                         "121873,-100,4,1,1,5,0,1",
                         "143942,-100,4,1,1,5,0,0",
                         "188080,-100,4,1,1,5,0,1"});

    TimingPointList test_2 = TimingPointList(input_2);
    QStringList output_2 = test_2.toStringList();
    qDebug() << output_2;

    test_2[0]->debugInfo();


    return a.exec();
}

