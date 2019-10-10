#include "editor.h"

char	*ft_itoa_static(intmax_t n)
{
	uintmax_t	tmpn;
	uintmax_t	div;
	static char	s[42];
	int			i;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	tmpn = n;
	div = 1;
	while (tmpn /= 10)
		div *= 10;
	while (div)
	{
		s[i++] = n / div % 10 + '0';
		div /= 10;
	}
	s[i] = '\0';
	return (s);
}

bool		same_pos(t_wall *w0, t_wall *w1)
{
	return (w0->point.x == w1->point.x && w0->point.y == w1->point.y);
}

static void	browse_sector(t_data *d, t_wall **w, int16_t *sectnum)
{
	int	s;
	int	k;
	int	l;

	s = -1;
	while (++s < d->numsectors && w[0]->neighborsect == -1)
	{
		if (s != *sectnum)
		{
			k = d->sectors[s].numwalls - 1;
			l = 0;
			while (l < d->sectors[s].numwalls)
			{
				w[2] = &d->walls[d->sectors[s].firstwallnum + k];
				w[3] = &d->walls[d->sectors[s].firstwallnum + l];
				if (same_pos(w[0], w[3]) && same_pos(w[1], w[2]))
				{
					w[0]->neighborsect = s;
					w[2]->neighborsect = *sectnum;
					break ;
				}
				k = l++;
			}
		}
	}
}

void		detect_neighbors(t_data *d, int16_t sectnum)
{
	int		npoints;
	t_wall	*w[4];
	int		i;
	int		j;

	npoints = d->sectors[sectnum].numwalls;
	if (npoints < 2)
		return ;
	i = npoints - 1;
	j = 0;
	while (j < npoints)
	{
		w[0] = &d->walls[d->sectors[sectnum].firstwallnum + i];
		w[1] = &d->walls[d->sectors[sectnum].firstwallnum + j];
		w[0]->neighborsect = -1;
		browse_sector(d, w, &sectnum);
		i = j++;
	}
}
