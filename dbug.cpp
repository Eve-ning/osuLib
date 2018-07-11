#include "dbug.h"

bool Dbug::debug_boundedInt() {
    BoundedInt a(1, 0, 10);
    BoundedInt b(2, 0, 10);

    // H: 11, R: 10
    a += 10; compareDebug(10, a); //  Max Bound

    // H: 6, R: 6
    a -= 5; compareDebug(6, a); // Value Check

    // H: -4, R: 0
    a -= 10; compareDebug(0, a); // Min Bound

    // H: 4, R: 4
    a += b * 4; compareDebug(4, a); // Check with another Bounded

    return true;
}

bool Dbug::debug_boundedDouble() {
    BoundedDouble a(1.0, 0.0, 10.0);
    BoundedDouble b(2.0, 0.0, 10.0);

    // H: 11, R: 10
    a += 10; compareDebug(10, a); //  Max Bound

    // H: 6.5, R: 6.5
    a -= 5.5; compareDebug(5.5, a); // Value Check

    // H: -4.5, R: 0
    a -= 10; compareDebug(0, a); // Min Bound

    // H: 3.5, R: 3.5
    a += b * 4; compareDebug(3.5, a); // Check with another Bounded

    return true;
}

bool Dbug::compareDebug(const double &expected, const double &given)
{
    qDebug() << (expected == given) << " | Expected: " << expected << " | Given: " << given;
    return expected == given;
}
