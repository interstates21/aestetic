#include "../includes/doom_nukem.h"

bool	same_pos(t_vec2f v1, t_vec2f v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

int		find_nei(t_data *d, t_vec2f v0, t_vec2f v1, int sect)
{
	int	s;
	int	w[2];

	s = -1;
	while (++s < d->numsectors)
	{
		w[0] = d->sectors[s].firstwallnum + d->sectors[s].numwalls - 1;
		w[1] = d->sectors[s].firstwallnum;
		while (w[1] < (d->sectors[s].firstwallnum + d->sectors[s].numwalls))
		{
			if (same_pos(d->walls[w[0]].point, v1) &&
					same_pos(d->walls[w[1]].point, v0) && (s != sect))
				return (s);
			w[0] = w[1]++;
		}
	}
	return (-1);
}

void	fix_neighborsects(t_data *d)
{
	int	s;
	int	w[2];

	s = -1;
	while (++s < d->numsectors)
	{
		w[0] = d->sectors[s].firstwallnum + d->sectors[s].numwalls - 1;
		w[1] = d->sectors[s].firstwallnum;
		while (w[1] < (d->sectors[s].firstwallnum + d->sectors[s].numwalls))
		{
			d->walls[w[0]].neighborsect = find_nei(d, d->walls[w[0]].point,
					d->walls[w[1]].point, s);
			w[0] = w[1]++;
		}
	}
}
