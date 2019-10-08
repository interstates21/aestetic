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


double	get_floorheight_player(t_data *d, int16_t sectnum)
{
	return (get_floceiheight(d, sectnum, v3_to_v2(d->cam.pos), 1));
}

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	return (get_floceiheight(d, sectnum, v3_to_v2(d->cam.pos), 0));
}

/*
**	Delta height between player and floor/ceil at point.
*/

double	get_floordh(t_data *d, t_sector *sect, t_vec2f v)
{
	return (get_floceiheight(d, sect - d->sectors, v, 1) -
			d->cam.pos.y);
}

double	get_ceildh(t_data *d, t_sector *sect, t_vec2f v)
{
	return (get_floceiheight(d, sect - d->sectors, v, 0) -
			d->cam.pos.y);
}
