/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_fix_data_to_save.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:54:22 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/26 13:54:24 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	Set all texture as unsued.
*/

static void	reset_used(t_data *d)
{
	t_texture_data *tmp;

	d->nb_used_texture = 0;
	tmp = d->texture_list->begin;
	while (tmp)
	{
		tmp->used = 0;
		tmp = tmp->next;
	}
}

void		set_poster_name(t_data *d)
{
	t_texture_data	*tmp;
	int				j;
	int				tex_num;

	tmp = d->posters_list->begin;
	tex_num = 0;
	while (tmp)
	{
		j = -1;
		while (++j < d->numwalls)
			if (d->walls[j].posterpicnum == tex_num)
				ft_strcpy(d->walls[j].poster_name, tmp->name);
		tex_num++;
		tmp = tmp->next;
	}
}

/*
**	set the corresponding texture name to each sector and walls structure.
*/

void		set_texture_name(t_data *d, t_sector *s, t_wall *w)
{
	t_texture_data	*tmp;
	int				j;
	int				tex_num;

	tmp = d->texture_list->begin;
	tex_num = 0;
	while (tmp)
	{
		j = -1;
		while (++j < d->numsectors)
		{
			if (s[j].floorpicnum == tex_num)
				ft_strcpy(s[j].floor_texture_name, tmp->name);
			if (s[j].ceilpicnum == tex_num)
				ft_strcpy(s[j].ceil_texture_name, tmp->name);
		}
		j = -1;
		while (++j < d->numwalls)
			if (w[j].middlepicnum == tex_num)
				ft_strcpy(w[j].texture_name, tmp->name);
		tex_num++;
		tmp = tmp->next;
	}
	set_poster_name(d);
}

/*
**	Browse all the texture and set as used,
**	all texture currently used in the map
*/

void		set_texture_used(t_data *d, t_sector *s, t_wall *w)
{
	t_texture_data	*tmp;
	int				j;
	int				tex_num;

	if (!d->texture_list)
		return ;
	reset_used(d);
	tmp = d->texture_list->begin;
	tex_num = 0;
	while (tmp)
	{
		j = -1;
		while (++j < d->numsectors && tmp->used != 1)
			if (s[j].floorpicnum == tex_num || s[j].ceilpicnum == tex_num)
				d->nb_used_texture +=
					(tmp->used = 1);
		j = -1;
		while (++j < d->numwalls && tmp->used != 1)
			if (w[j].lowerpicnum == tex_num || w[j].middlepicnum == tex_num ||
				w[j].upperpicnum == tex_num)
				d->nb_used_texture +=
					(tmp->used = 1);
		tex_num++;
		tmp = tmp->next;
	}
}
