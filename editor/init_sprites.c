/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:52:48 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:53:45 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void			part_2(t_sprite *s)
{
	if (ft_strequ("chandelier.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 0, .collision = 0, .dmg = 5,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_CEIL, .sect = -1};
	else if (ft_strequ("jetpack.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 1, .collision = 0, .dmg = 0,
		.heal = 0, .interactive = 1, .jetpack = 1, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else if (ft_strequ("pikachu.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 0, .collision = 0, .dmg = 0,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else
		*s = (t_sprite){ .ammo = 0, .autopick = 0, .collision = 1, .dmg = 0,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
}

static void			make_it_happen(t_sprite *s, char *p)
{
	if (ft_strequ("cryo_balista.bmp", s->name))
		*s = (t_sprite){ .ammo = 5, .autopick = 1, .collision = 0, .dmg = 0,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else if (ft_strequ("healpack.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 1, .collision = 0, .dmg = 0,
		.heal = 25, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else if (ft_strequ("BAL1A0.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 0, .collision = 1, .dmg = 15,
		.heal = 0, .interactive = 1, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else if (ft_strequ("BAL1B0.bmp", s->name))
		*s = (t_sprite){ .ammo = 5, .autopick = 1, .collision = 0, .dmg = 0,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else if (ft_strequ("barrel.bmp", s->name))
		*s = (t_sprite){ .ammo = 0, .autopick = 0, .collision = 1, .dmg = 0,
		.heal = 0, .interactive = 0, .jetpack = 0, .k_num = -1, .key = 0,
		.pos = P_FLOOR, .sect = -1};
	else
		part_2(s);
	read_bmp(&s->texture, p);
}

void				init_sprites(t_ed *e)
{
	DIR				*dir;
	struct dirent	*data;
	char			*tmp[2];
	int				i;

	dir = NULL;
	tmp[0] = "../texts/objects/objects/";
	reopen(&dir, tmp[0]);
	while ((data = readdir(dir)))
		if (bmp_check(data))
			e->n_sprites += 1;
	e->sprites = (t_sprite*)malloc(sizeof(t_sprite) * e->n_sprites);
	reopen(&dir, tmp[0]);
	i = 0;
	while ((data = readdir(dir)))
		if (bmp_check(data))
		{
			tmp[1] = ft_strjoin(tmp[0], data->d_name);
			ft_strcpy(e->sprites[i].name, data->d_name);
			make_it_happen(&e->sprites[i++], tmp[1]);
			free(tmp[1]);
		}
	closedir(dir);
}
