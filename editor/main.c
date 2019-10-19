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
	e->n_sprites = 0;
}

static void	do_magic(int fd)
{
	t_ed	ed;

	ed.fd = fd;
	init_sdl(&ed.sdl);
	ground(&ed);
	init_textures(&ed);
	init_monsters(&ed);
	init_sprites(&ed);
	//loop(&ed);
	//saving_screen();
	//save();
}

static void	run(char *mapname)
{
	int 	fd;

	//if (open(mapname, O_RDONLY) != -1)
	//	print_err("Map already exists");
	//fd = open(mapname, O_CREAT | O_RDWR);
	do_magic(2);
	close(2);
}

void	print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	exit(1);
}

int			main(int argc, char **argv) {
	//if (argc != 2)
	//	print_err("Usage: ./editor [map_name]");
	run(argv[1]);
	system("leaks --quiet dm_editor");
	return (0);
}
