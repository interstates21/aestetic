/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:16:55 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:16:56 by akolomoi         ###   ########.fr       */
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
	e->selection.sector = -1;
	e->selection.select = 2;
	e->p_ang = 0.0;
	e->start = 0;
	e->n_all_w = 0;
}

static void	do_magic(t_ed *ed, int fd)
{
	ed->fd = fd;
	ground(ed);
	init_font(ed);
	init_textures(ed);
	init_monsters(ed);
	init_sprites(ed);
	init_default_sect(ed);
}

static t_v3	new_pos(t_ed *e)
{
	int		i;
	int		j;

	i = -1;
	while (++i < e->n_sect && (j = -1))
		while (++j < e->seclist[i].n_walls)
		{
			e->seclist[i].walls[j].v1.x >>= 3;
			e->seclist[i].walls[j].v1.y >>= 3;
			e->seclist[i].walls[j].v2.x >>= 3;
			e->seclist[i].walls[j].v2.y >>= 3;
		}
	return ((t_v3){
	(e->seclist[0].walls[1].v1.x + e->seclist[0].walls[0].v1.x
	+ e->seclist[0].walls[2].v1.x + e->seclist[0].walls[3].v1.x) >> 2,
	e->seclist[0].height[T_FLOOR],
	(e->seclist[0].walls[1].v1.y + e->seclist[0].walls[0].v1.y
	+ e->seclist[0].walls[2].v1.y + e->seclist[0].walls[3].v1.y) >> 2
	});
}

static void	run(char *mapname)
{
	char	*tmp;
	t_ed	ed;
	t_sdl	sdl;

	sdl_init(&sdl);
	sdl_init_renderer(&sdl);
	tmp = add_path(mapname);
	if (open(tmp, O_RDONLY) != -1)
		print_err("Map already exists");
	free(tmp);
	do_magic(&ed, 2);
	render_manager(&sdl, &ed);
	ed.player = new_pos(&ed);
	find_used_tex(&ed);
	save_world(&ed, mapname);
	close(2);
}

int			main(int argc, char **argv)
{
	if (argc != 2)
		print_err("Usage: ./editor [map_name]");
	run(argv[1]);
	return (0);
}
