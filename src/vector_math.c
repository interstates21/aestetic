#include "alt.h"

t_vt new_v2f(double x, double y)
{
    t_vt a;

    a.x = x;
    a.y = y;
    a.z = UNDEF;
    return (a);
}


t_vt v_minus(t_vt a, t_vt b)
{
    t_vt c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;

    return c;
}

t_v2i new_v2(int x, int y)
{
    t_v2i a;

    a.x = x;
    a.y = y;
    return (a);
}
