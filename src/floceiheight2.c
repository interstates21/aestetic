#include "../includes/doom_nukem.h"

/*
**	Height of the floor/ceil under the player.
*/


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

int	ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

int	ft_min(int a, int b)
{
	return ((a > b) ? b : a);
}

double	get_floorheight_player(t_data *d, int16_t sectnum)
{
	return (get_floorheight_point(d, sectnum, v3_to_v2(d->cam.pos)));
}

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	return (get_ceilheight_point(d, sectnum, v3_to_v2(d->cam.pos)));
}

/*
**	Delta height between player and floor/ceil at point.
*/

double	get_floordh(t_data *d, t_sector *sect, t_vec2f v)
{
	return (get_floorheight_point(d, sect - d->sectors, v) -
			d->cam.pos.y);
}

double	get_ceildh(t_data *d, t_sector *sect, t_vec2f v)
{
	return (get_ceilheight_point(d, sect - d->sectors, v) -
			d->cam.pos.y);
}
