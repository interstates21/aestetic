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

// сцена нужна для проверки по секторам
int		player_init(t_scene *s, char *l)
{
	int		sect;
	int 	i;
	t_v2f	v;
	double	ang;

	i = 0;
	if (!fetch_f(&v.x, l, &i) || !fetch_f(&v.y, l, &i) || !fetch_f(&ang, l, &i)
	|| !fetch_int(l, &sect) || sect >= s->n_sectors)
		return (0);
	s->player = (t_player){(t_v3f){v.x, v.y, 0}, (t_v3f){0, 0, 0}, ang, 0, 0,
	0, 0, 0, sect};
	return (1);
}
