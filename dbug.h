#ifndef DBUG_H
#define DBUG_H

#include "bounded/boundedint.h"
#include "bounded/boundeddouble.h"
#include <QDebug>

class Dbug
{
public:
    Dbug();

    static void full_debug() {
        qDebug() << "[Debug]";

        if (debug_boundedInt()) { qDebug() << "BoundedInt Pass."; }
        if (debug_boundedDouble()) { qDebug() << "BoundedDouble Pass."; }
    }

private:

    static bool debug_boundedInt();
    static bool debug_boundedDouble();
};

#endif // DBUG_H
