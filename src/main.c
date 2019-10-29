/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:40:05 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 18:52:40 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	set_door_active(t_env *d)
{
	short	i;

	i = 0;
	while (i < d->n_walls)
	{
		d->anim_door[i] = 0.0;
		d->door_active[i] = 0.0;
		i++;
	}
}

void	init_everything(t_env *d, char *map)
{
	int i;
	int	j;
	int	k;

	i = -1;
	while (++i < N_MONSTER_TYPES && (j = -1))
		while (++j < MAX_STATE_MONSTER && (k = -1))
			while (++k < MAXNBOFANIMATION)
				d->monster_text[i][j][k] = NULL;
	to_loading_map(d, map);
	set_door_active(d);
	to_load_numbpic(d);
	play_initialization(d, &d->player);
	monters_inicialization(d);
	proj_initialization(d);
	if (d->sect_begin < 0)
		print_err("error");
	if (SDL_SetRelativeMouseMode(SDL_TRUE) == -1)
		print_err("error");
	d->player_floor_h = height_play_fl_val(d, d->this_sect);
	d->player_ceil_h = height_play_cl_val(d, d->this_sect);
	music_player(d, MAIN_MUSIC);
	to_sector_load(d);
	loop(d);
}

void	run(char *mapname)
{
	t_env		d;
	SDL_Event	e;
	int			z;

	z = 0;
	font_initialize(&d);
	d.loaded = 0;
	sdl_inicialization(&(d.sdl));
	TTF_Init();
	d.g_font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 25);
	keyboard_battons(&(d.keys));
	while (z == 0)
		z = displaing_backgr(&d, e);
	d.z_buff = pix_val_scr();
	ft_strncpy(d.nextmap, mapname, 100);
	init_everything(&d, d.nextmap);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		print_err("Wrong number of args =(");
	if (!check_inp_par(argv[1]))
		print_err("Wrong mapname");
	run(argv[1]);
}
