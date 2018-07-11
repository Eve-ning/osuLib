#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"
#include "hitobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Dbug::full_debug();

    NormalNote normal_note;
    normal_note.debugInfo();

    return a.exec();
}

