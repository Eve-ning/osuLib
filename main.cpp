#include <QCoreApplication>
#include <QDebug>
#include "boundedint.h"

bool debugLib();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BoundedInt one, two;

    one = 1;
    two = 2;

    BoundedInt three;

    three = one + two;

    qDebug() << three;

    debugLib();

    return a.exec();
}

bool debugLib(){
    return true;
}
