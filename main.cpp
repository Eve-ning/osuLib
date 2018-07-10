#include <QCoreApplication>
#include <QDebug>
#include "dbug.h"

bool debugLib();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Dbug::full_debug();

    debugLib();

    return a.exec();
}

bool debugLib(){
    return true;
}
