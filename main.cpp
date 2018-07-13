#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"
#include "osu_primitives/hitobjectlist.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dbug::full_debug();

    HitObjectList test = HitObjectList();

    test.append(std::make_shared<NormalNote>(NormalNote()));

    test[0]->debugInfo();

    return a.exec();
}

