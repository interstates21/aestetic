/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:49:48 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:53:22 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		save_sector(t_ed *m, t_sect *e)
{
	t_sdtsector	s;
	int			i;

	s = (t_sdtsector){e->start_wall, e->n_walls, e->height[H_FLOOR],
	e->height[H_CEIL], e->tex[T_FLOOR], e->tex[T_CEIL], 1.0, 0, "", "",
	e->height[H_CEIL] > 190 ? 1 : 0,
	NULL, e->slope[H_FLOOR], e->slope_rot[H_FLOOR], e->slope[H_CEIL],
	e->slope_rot[H_CEIL], 0, 0, e->is_elev, e->is_finish, e->is_dmg};
	i = -1;
	while (++i < 100)
	{
		s.floor_texture_name[i] = m->texlist[e->tex[H_FLOOR]].name[i];
		s.ceil_texture_name[i] = m->texlist[e->tex[H_CEIL]].name[i];
	}
	if (write(m->fd, &s, sizeof(t_sdtsector)) < 0
	|| write(m->fd, m->texlist[e->tex[H_FLOOR]].name, MAX_NAME) < 0
	|| write(m->fd, m->texlist[e->tex[H_CEIL]].name, MAX_NAME) < 0)
		print_err("failed to save sector");
}

static void		write_walls(t_ed *e, t_wall *w)
{
	t_stdwall	s;
	int			i;
	int16_t		val;

	val = w->is_portal;
	s = (t_stdwall){(t_v2f){w->v1.x, w->v1.y}, w->tex[T_FLOOR],
	w->tex[T_WALL], w->tex[T_CEIL], 0, val, "", "", 1,
	-1, 0, -1, 0};
	if (ft_strequ(e->texlist[w->tex[T_WALL]].name, "../texts/wiremesh.bmp")
	|| ft_strequ(e->texlist[w->tex[T_WALL]].name, "../texts/DOOR12_1.bmp")
	|| ft_strequ(e->texlist[w->tex[T_WALL]].name, "../texts/M1_1.bmp"))
		s.is_transparent = 1;
	i = -1;
	while (++i < MAX_NAME)
	{
		s.texture_name[i] = e->texlist[w->tex[T_WALL]].name[i];
		s.poster_name[i] = 0;
	}
	if (write(e->fd, &s, sizeof(t_stdwall)) < 0
		|| write(e->fd, e->texlist[w->tex[H_FLOOR]].name, MAX_NAME) < 0
		|| write(e->fd, s.poster_name, MAX_NAME) < 0)
		print_err("failed to save wall");
}

void			write_secors(t_ed *e)
{
	int		i;
	int		j;
	int16_t tmp;

	tmp = e->n_sect;
	if (write(e->fd, &tmp, sizeof(int16_t)) < 0)
		print_err("failed to save n_sect");
	i = -1;
	while (++i < e->n_sect)
		save_sector(e, &e->seclist[i]);
	tmp = e->n_all_w;
	if (write(e->fd, &tmp, sizeof(int16_t)) < 0)
		print_err("failed to save n_walls");
	i = -1;
	while (++i < e->n_sect && (j = -1))
	{
		while (++j < e->seclist[i].n_walls)
			write_walls(e, &e->seclist[i].walls[j]);
	}
}
