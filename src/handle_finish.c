/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:58:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 23:07:52 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	monst_free(t_data *d, int i, int j, int k)
{
	if (d->monster_text[i][j][k])
		SDL_FreeSurface(d->monster_text[i][j][k]);
	d->monster_text[i][j][k] = NULL;
}

void	monst_and_assets_free(t_data *d, int i)
{
	int	j;
	int	k;

	j = -1;
	while (++i < MAXTYPEMONSTERS)
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

void	weap_free(t_data *d)
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
			SDL_FreeSurface(d->projectile_tex[i][j]);
	}
}

void	all_free(t_data *d)
{
	int	i;

	i = -1;
	if (d->nb_assets > 0)
		while (++i < d->numsectors)
			free(d->assets[i]);
	if (d->nummonsters > 0)
		free(d->monsters);
	i = -1;
	if (d->nb_textures > 0)
		while (++i < d->nb_textures)
			free(d->tex_name_list[i]);
	i = -1;
	if ((intptr_t)d->posters > 0)
	{
		while (++i < d->nb_posters)
			SDL_FreeSurface(d->posters[i]);
		free(d->posters);
	}
	weap_free(d);
	monst_and_assets_free(d, -1);
	free(d->tex_name_list);
	free(d->assets);
	d->tex_name_list = NULL;
	d->assets = NULL;
}

void	free_sectors_sprites(t_data *d, short i)
{
	t_sprite_list	*list;
	t_sprite_list	*need_free;

	list = d->sectors[i].sprite_list;
	d->sectors[i].sprite_list = NULL;
	while (list)
	{
		need_free = list->next;
		free(list);
		list = need_free;
	}
}

void	handle_finish(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->nb_textures)
		SDL_FreeSurface(d->textures[i]);
	free(d->textures);
	d->textures = NULL;
	i = -1;
	while (++i < MAX_PROJECTILES)
		d->projectiles[i].is_active = false;
	i = -1;
	while (++i < d->numsectors)
		free_sectors_sprites(d, i);
	all_free(d);
	init_everything(d, d->nextmap);
}
