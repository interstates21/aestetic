/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:53:07 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 16:09:06 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

//not refact

static void	set_var_reorder_sprite(t_sprite_list **list, t_sector *sec, int *i,
		bool type)
{
	if (type == SET)
	{
		list[2] = sec->sprite_list->next;
		list[1] = sec->sprite_list;
		*i = 0;
	}
	if (type == INCREMENT)
	{
		*i = *i + 1;
		list[0] = list[1];
		list[1] = list[2];
		list[2] = list[2]->next;
	}
}

void		change_list(t_sprite_list *one, t_sprite_list *two,
		t_sprite_list *prev)
{
	prev->next = two;
	one->next = two->next;
	two->next = one;
}

void		reorder_sprites_algo(t_env *d, t_sector *sec, double *vla,
		t_sprite_list **list)
{
	double		distance;
	int			i;

	set_var_reorder_sprite(list, sec, &i, SET);
	while (list[2])
	{
		if (vla[i] < vla[i + 1])
		{
			distance = vla[i];
			vla[i] = vla[i + 1];
			vla[i + 1] = distance;
			if (i != 0)
			{
				change_list(list[1], list[2], list[0]);
				reorder_sprites_algo(d, sec, vla, list);
				return ;
			}
			list[1]->next = list[2]->next;
			list[2]->next = sec->sprite_list;
			sec->sprite_list = list[2];
			reorder_sprites_algo(d, sec, vla, list);
			return ;
		}
		set_var_reorder_sprite(list, sec, &i, INCREMENT);
	}
}

void		set_vla(t_sprite_list *tmp, double *vla, t_env *d)
{
	short	i;

	i = -1;
	while (tmp && (++i))
	{
		if (tmp->type == IS_PROJECTILE)
			vla[i] = vec3f_length(v3_min(d->cam.pos,
						d->anim_rots[tmp->id].pos));
		if (tmp->type == IS_MONSTER)
			vla[i] = vec3f_length(v3_min(d->cam.pos,
				new_v3(d->monsters[tmp->id].pos.x,
					0.0, d->monsters[tmp->id].pos.y)));
		tmp = tmp->next;
	}
}

void		reorder_sprite(t_env *d, t_sector *sect)
{
	t_sprite_list	*tmp;
	short			i;
	double			*vla;
	t_sprite_list	*list[3];

	i = -1;
	tmp = sect->sprite_list;
	while (tmp && (++i))
		tmp = tmp->next;
	if (i > 1)
	{
		vla = pure_malloc(sizeof(*vla) * i, "alloc reorder sprites failed");
		tmp = sect->sprite_list;
		set_vla(tmp, vla, d);
		reorder_sprites_algo(d, sect, vla, &list[0]);
		free(vla);
	}
}
