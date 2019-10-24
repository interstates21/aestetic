#include "../includes/doom_nukem.h"

static bool	is_part(t_v2_pair wall_vects, t_v2_pair vects, bool not_itself)
{
	bool	pos1;
	bool	pos2;

	pos1 = SAME_POS(wall_vects.v1, vects.v1);
	pos2 = SAME_POS(wall_vects.v2, vects.v2);
	return (pos1 && pos2 && not_itself);
}

static int	calculate_next_sect(t_data *d, t_range old_range, int old_current)
{
	int			current;
	t_v2_pair	p1;
	t_range		range;
	t_vec2f		v0;
	t_vec2f		v1;

	v0 = d->walls[old_range.max].point;
	v1 = d->walls[old_range.min].point;
	current = -1;
	while (++current < d->numsectors)
	{
		range = make_range(d->sectors[current].firstwallnum,
		d->sectors[current].firstwallnum + d->sectors[current].numwalls - 1);
		while (range.min < (d->sectors[current].firstwallnum +
												d->sectors[current].numwalls))
		{
			p1 = new_v2_pair(d->walls[range.max].point,
													d->walls[range.min].point);
			if (is_part(p1, new_v2_pair(v1, v0), current != old_current))
				return (current);
			range.max = range.min;
			range.min++;
		}
	}
	return (-1);
}

void	next_sect_fix(t_data *d)
{
	int		current;
	int		min;
	int		max;
	int		sum;
	t_range range;

	range.min = 0;
	range.max = 0;
	current = 0;
	while (current < d->numsectors)
	{
		max = d->sectors[current].firstwallnum +
											d->sectors[current].numwalls - 1;
		min = d->sectors[current].firstwallnum;
		sum = d->sectors[current].firstwallnum + d->sectors[current].numwalls;
		range = make_range(min, max);
		while (range.min < sum)
		{
			d->walls[range.max].neighborsect =
										calculate_next_sect(d, range, current);
			range.max = range.min;
			range.min++;
		}
		current++;
	}
}
