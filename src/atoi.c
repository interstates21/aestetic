/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:27:46 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/24 20:04:26 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	div_wl(int n, int div, char *s, int i)
{
	while (div)
	{
		s[i++] = n / div % 10 + '0';
		div /= 10;
	}
	s[i] = '\0';
}

char		*ft_itoa_static(int n)
{
	int			tmpn;
	int			div;
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
	div_wl(n, div, s, i);
	return (s);
}

void	swap_tabs(short *tab, short *tmp_tab)
{
	short	i;

	i = 0;
	while (tmp_tab[i] != -1)
	{
		tab[i] = tmp_tab[i];
		tmp_tab[i] = -1;
		i++;
	}
	while (tab[i] != -1)
	{
		tab[i] = -1;
		i++;
	}
}

void	set_tab(t_data *d, short sect_to_scan, short *tab, short old_sect)
{
	short	i;
	short	j;
	short	k;
	short	l;

	k = 0;
	while (tab[k] != -1)
		k++;
	i = d->sectors[sect_to_scan].firstwallnum - 1;
	j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 &&
				d->walls[i].neighborsect != old_sect)
		{
			l = -1;
			while (tab[++l] != -1)
				if (tab[l] == d->walls[i].neighborsect)
					break ;
			if (tab[l] == -1)
			{
				tab[k] = d->walls[i].neighborsect;
				k++;
			}
		}
}
