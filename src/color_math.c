#include "alt.h"

t_rgb   new_rgb(int r, int g, int b)
{
    t_rgb a;

    a.r = r;
    a.b = g;
    a.g = b;
    a.a = 255; // may be useful in future

    return (a);
}
