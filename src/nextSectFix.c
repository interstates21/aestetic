#include "../includes/doom_nukem.h"

static bool	isPart(t_v2_pair wallVects, t_v2_pair vects, bool notItself) {
	bool	pos1;
	bool   	pos2;

	pos1 = SAME_POS(wallVects.v1, vects.v1);
	pos2 = SAME_POS(wallVects.v2, vects.v2);
	return (pos1 && pos2 && notItself);
}

static int		calculateNextSect(t_data *d, t_range oldRange, int oldCurrent)
{
	int 		current;
	t_v2_pair	p1;
	t_range		range;
	t_vec2f 	v0;
	t_vec2f 	v1;

	v0 = d->walls[oldRange.max].point;
	v1 = d->walls[oldRange.min].point;
	current = 0;
	while (current < d->numsectors)
	{
		range = make_range(d->sectors[current].firstwallnum, d->sectors[current].firstwallnum + d->sectors[current].numwalls - 1);
		while (range.min < (d->sectors[current].firstwallnum + d->sectors[current].numwalls))
		{
			p1 = new_v2_pair(d->walls[range.max].point, d->walls[range.min].point);
			if (isPart(p1, new_v2_pair(v1, v0), current != oldCurrent))
				return (current);
			range.max = range.min;
			range.min++;
		}
		current++;
	}
	return (-1);
}

void	nextSectFix(t_data *d)
{
	int	current;
	int min;
	int max;
	int sum;
	t_range range;

	range.min = 0;
	range.max = 0;
	current = 0;
	while (current < d->numsectors)
	{
		max = d->sectors[current].firstwallnum + d->sectors[current].numwalls - 1;
		min = d->sectors[current].firstwallnum;
		sum = d->sectors[current].firstwallnum + d->sectors[current].numwalls;
		range = make_range(min, max);
		while (range.min < sum)
		{
			d->walls[range.max].neighborsect = calculateNextSect(d, range, current);
			range.max = range.min;
			range.min++;
		}
		current++;
	}
}
