/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:11:20 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/15 17:11:21 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	ground(t_ed *e)
{
	e->seclist = NULL;
	e->texlist = NULL;
	e->n_sprites = 0;
	e->n_walls = 0;
	e->n_sect = 0;
	e->selection.drawing = 0;
}

static void	do_magic(t_ed *ed, int fd)
{
	ed->fd = fd;
	// init_sdl(&ed.sdl);
	ground(ed);
	init_font(ed);
	init_textures(ed);
	init_monsters(ed);
	init_sprites(ed);
	init_default_sect(ed);
	//loop(&ed);
	//saving_screen();
	//save();
}

static void	run(char *mapname)
{
	int 	fd;
    t_ed    ed;
    t_sdl   sdl;

    sdl_init(&sdl);
    sdl_init_renderer(&sdl);

	//if (open(mapname, O_RDONLY) != -1)
	//	print_err("Map already exists");
	//fd = open(mapname, O_CREAT | O_RDWR);
	do_magic(&ed, 2);
    render_manager(&sdl, &ed);
	//todo sdl clean
	close(2);
}

int			main(int argc, char **argv) {
	//if (argc != 2)
	//	print_err("Usage: ./editor [map_name]");
	run(argv[1]);
	system("leaks --quiet dm_editor");
	return (0);
}
