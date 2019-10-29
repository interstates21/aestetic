/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:40:05 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 21:38:20 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	free_lst(short id, t_sprite_list *tmp, t_sprite_list *tmp_prev,
	uint8_t type_to_destroy)
{
	if (tmp->id == id && tmp->type == type_to_destroy)
	{
		tmp_prev->next = tmp->next;
		free(tmp);
		return ;
	}
}

void	ini_lst(t_sprite_list **tmp, t_env *d, int *sectnum, int mod)
{
	if (mod == 1)
	{
		tmp[0] = d->sectors[sectnum[0]].sprite_list;
		tmp[1] = d->sectors[sectnum[1]].sprite_list;
		tmp[2] = tmp[0];
	}
	else if (mod == 2)
	{
		tmp[0]->next = tmp[1];
		d->sectors[sectnum[1]].sprite_list = tmp[0];
	}
}

void	mailing_deleted(short id, t_sec *sector, uint8_t type_to_destroy)
{
	t_sprite_list	*tmp;
	t_sprite_list	*tmp_prev;

	tmp = sector->sprite_list;
	if (!(tmp))
		return ;
	if (tmp->id == id && tmp->type == type_to_destroy)
	{
		sector->sprite_list = tmp->next;
		free(tmp);
		return ;
	}
	tmp_prev = tmp;
	while (tmp)
	{
		free_lst(id, tmp, tmp_prev, type_to_destroy);
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

void	list_swp(uint8_t type, uint16_t id, t_env *d, int sectnum[2])
{
	t_sprite_list *tmp[3];

	ini_lst(tmp, d, sectnum, 1);
	if (tmp[0]->type == type && tmp[0]->id == id)
		d->sectors[sectnum[0]].sprite_list = tmp[0]->next;
	else
	{
		while (tmp[0])
		{
			if (tmp[0]->type == type && tmp[0]->id == id)
			{
				tmp[2]->next = tmp[0]->next;
				break ;
			}
			tmp[2] = tmp[0];
			tmp[0] = tmp[0]->next;
		}
	}
	ini_lst(tmp, d, sectnum, 2);
}
