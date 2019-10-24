#include "../includes/doom_nukem.h"

t_range	make_range(int min, int max)
{
	t_range r;

	r.min = min;
	r.max = max;
	r.t = 0;

	return (r);
}
