/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:58:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:06:06 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	monst_free(t_env *d, int i, int j, int k)
{
	if (d->monster_text[i][j][k])
		SDL_FreeSurface(d->monster_text[i][j][k]);
	d->monster_text[i][j][k] = NULL;
}

void	monst_and_assets_free(t_env *d, int i)
{
	int	j;
	int	k;

	j = -1;
	while (++i < N_MONSTER_TYPES)
	{
		k = -1;
		while (++j < 10)
			while (++k < MAXNBOFANIMATION)
				monst_free(d, i, j, k);
		k = 9;
		while (++k < 19)
			monst_free(d, i, k, 0);
	}
	i = -1;
	if (d->nb_assets_texture > 0)
		while (++i < d->nb_assets_texture)
			SDL_FreeSurface(d->assets_texture[i]);
	free(d->assets_texture);
}

void	weap_free(t_env *d)
{
	int			i;
	int			j;
	int			*numb_texturs;
	int			*numb_proj;

	numb_texturs = (int[3]){13, 15, 3};
	numb_proj = (int[3]){20, 5, 5};
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < numb_texturs[i])
			SDL_FreeSurface(d->weapon_tex[i][j]);
		j = -1;
		while (++j < numb_proj[i])
			SDL_FreeSurface(d->anim_rot_text[i][j]);
	}
}

void	all_free(t_env *d)
{
	int	i;

	i = -1;
	if (d->objects_n > 0)
		while (++i < d->n_sect)
			free(d->objects[i]);
	if (d->monst_n > 0)
		free(d->monsters);
	i = -1;
	if (d->n_texts > 0)
		while (++i < d->n_texts)
			free(d->tex_name_list[i]);
	i = -1;
	if ((intptr_t)d->posters > 0)
	{
		while (++i < d->n_posters)
			SDL_FreeSurface(d->posters[i]);
		free(d->posters);
	}
	weap_free(d);
	monst_and_assets_free(d, -1);
	free(d->tex_name_list);
	free(d->objects);
	d->tex_name_list = NULL;
	d->objects = NULL;
}

void	ending_hd(t_env *d)
{
	int	i;
	int	f;

	i = -1;
	while (++i < d->n_texts)
		SDL_FreeSurface(d->texts[i]);
	free(d->texts);
	d->texts = NULL;
	i = -1;
	while (++i < N_ANIM_ROTS)
		d->anim_rots[i].is_active = false;
	i = -1;
	while (++i < d->n_sect)
		del_mem_spr(d, i);
	ending(d);
	SDL_Delay(500);
	all_free(d);
	exit(1);
}
