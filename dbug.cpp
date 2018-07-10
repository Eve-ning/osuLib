#include "dbug.h"

bool Dbug::debug_boundedInt() {
    BoundedInt a(1, 0, 10);
    BoundedInt b(2, 0, 10);

    a += 10; if (a != 10) { return false; } // Max Bound
    a -= 5;  if (a != 5)  { return false; } // Value Check
    a -= 10; if (a != 0)  { return false; } // Min Bound
    a += b;  if (a != 2)  { return false; } // Check with another Bounded

    return true;
}

bool Dbug::debug_boundedDouble() {
    BoundedDouble a(1.0, 0.0, 10.0);
    BoundedDouble b(2.0, 0.0, 10.0);

    a += 10.0; if (a != 10.0) { return false; } // Max Bound
    a -= 5.0;  if (a != 5.0)  { return false; } // Value Check
    a -= 10.0; if (a != 0)    { return false; } // Min Bound
    a += b;    if (a != 2.0)  { return false; } // Check with another Bounded

    return true;
}
