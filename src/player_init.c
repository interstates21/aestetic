/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:17:00 by akolomoi          #+#    #+#             */
/*   Updated: 2019/08/21 17:17:01 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

static int	gut_check(char *s)
{
	int		db;
	int 	old;
	int 	res;
	int 	i;

	res = 0;
	db = 1;
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		old = res;
		while (i >= 0 && (ft_isdigit(s[i]) || s[i] == '.'))
		{
			db = s[i] ^ '.' ? db : db - 1 ;
			if (db < 0)
				return (0);
			res = res ^ old ? res : res + 1;
			i--;
		}
		db = 1;
		i--;
	}
	return (res == 4);
}

// сцена нужна для проверки по секторам
int			player_init(t_scene *s, char *l)
{
	double	sect;
	int 	i;
	t_v2f	v;
	double	ang;

	i = 0;
	if (!gut_check(l))
		return (0);
	fetch_f(&v.x, l, &i);
	fetch_f(&v.y, l, &i);
	fetch_f(&ang, l, &i);
	fetch_f(&sect, l, &i);
	s->player = (t_player){(t_v3f){v.x, v.y, 0}, (t_v3f){0, 0, 0}, ang, 0, 0,
	0, 0, 0, (int)floor(sect)};
	return (1);
}
