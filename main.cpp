#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"
#include "osu_primitives/hitobjectlist.h"
#include "osu_primitives/timingpointlist.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dbug::full_debug();





    return a.exec();
}

