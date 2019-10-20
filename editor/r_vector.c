#include "../includes/editor.h"

t_v2 new_v2(int a, int b) {
    t_v2 v;

    v.x = a;
    v.y = b;

    return (v);
}


bool v2_compare(t_v2 a, t_v2 b, int r) {
    if (a.y - r <= b.y && a.y + r >= b.y)
        if (a.x - r <= b.x && a.x + r >= b.x)
            return (true);
    return (false);
}