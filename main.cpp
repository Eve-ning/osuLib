#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"
#include "osu_primitives/hitobjectlist.h"
#include "osu_primitives/timingpointlist.h"
#include "osu_algorithms/osualgorithm.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dbug::primitive_debug();
    DEBUGSEP;
    Dbug::algorithm_debug();


    return a.exec();
}
