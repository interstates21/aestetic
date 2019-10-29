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

static void	if_it_loops(t_sprite_list **lt, t_sec *sec, int *j,
bool type)
{
	*j = type == INCREMENT ? *j + 1 : *j;
	*j = type == SET ? 0 : *j;
	lt[0] = type == INCREMENT ? lt[1] : lt[0];
	lt[1] = type == INCREMENT ? lt[2] : lt[1];
	lt[2] = type == INCREMENT ? lt[2]->next : lt[2];
	lt[2] = type == SET ? sec->sprite_list->next : lt[2];
	lt[1] = type == SET ? sec->sprite_list : lt[1];
}

void		sp_alg(t_env *d, t_sec *sec, double *smh,
		t_sprite_list **lt)
{
	int			j;

	if_it_loops(lt, sec, &j, SET);
	while (lt[2])
	{
		if (smh[j] < smh[j + 1])
		{
			swap_vals(&smh[j], &smh[j + 1]);
			if (j != 0)
			{
				change_list(lt[1], lt[2], lt[0]);
				sp_alg(d, sec, smh, lt);
				return ;
			}
			lt[1]->next = lt[2]->next;
			lt[2]->next = sec->sprite_list;
			sec->sprite_list = lt[2];
			sp_alg(d, sec, smh, lt);
			return ;
		}
		if_it_loops(lt, sec, &j, INCREMENT);
	}
}

void		reset_smh(t_sprite_list *some_val, double *smh, t_env *d)
{
	short	j;

	j = -1;
	while (some_val && (j += 1))
	{
		smh[j] = some_val->type == IS_PROJECTILE
		? get_smh(d->anim_rots[some_val->id].pos, d->cam.pos)
		: smh[j];
		smh[j] = some_val->type == IS_MONSTER
		? get_smh(new_v3(d->monsters[some_val->id].pos.x, 0.0,
		d->monsters[some_val->id].pos.y), d->cam.pos)
		: smh[j];
		some_val = some_val->next;
	}
}

void		reorder_sprite(t_env *d, t_sec *sect)
{
	double			*smh;
	t_sprite_list	*lt[3];
	short			j;
	t_sprite_list	*some_val;

	j = -1;
	smh = NULL;
	some_val = sect->sprite_list;
	while (some_val && (++j))
		some_val = some_val->next;
	j - 0b1 > 0x0 ? pure_malloc(sizeof(*smh) * j,
	"alloc reorder sprites failed") : skip(NULL);
	some_val = j - 0b1 > 0x0 ? sect->sprite_list : some_val;
	j - 01 > 0x0 ? reset_smh(some_val, smh, d) : skip(NULL);
	j - 0b1 > 0b0 ? sp_alg(d, sect, smh, &lt[00]) : skip(NULL);
	j - 0x1 > 00 ? free(smh) : skip(NULL);
}
