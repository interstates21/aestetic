/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:10:27 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:51:35 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	nice_grid(t_ed *ed)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ED_W && (j = -1))
		while (++j < ED_H)
			if (j % GRID_GAP && i % GRID_GAP)
				sdl_put_pix(&(ed->pixels), i, j, GRID_COL_1);
			else
				sdl_put_pix(&(ed->pixels), i, j, GRID_COL_2);
}

static void	init_render(t_ed *ed)
{
	ed->pixels = get_screen_pixels();
	ed->controller.mouse = new_v2(0, 0);
	ed->controller.mouse_is_pressed = false;
	ed->selection.selected_wall = NULL;
	ed->selection.selected_vertex = NULL;
	ed->texture_picker = NULL;
	ed->selection.monster = -1;
	ed->selection.sprite = -1;
}

t_wall		new_wall(int x1, int y1, int x2, int y2)
{
	t_wall	wall;

	wall.v1 = new_v2(x1, y1);
	wall.v2 = new_v2(x2, y2);
	wall.is_door = 0;
	wall.is_portal = -1;
	return (wall);
}

void		render_sector(t_ed *ed, t_sect *s)
{
	Uint32	color;
	int		i;

	i = 0;
	while (i < s->n_walls)
	{
		if (ed->selection.selected_wall == &s->walls[i])
			color = RED;
		else if (s->walls[i].is_door)
			color = DOOR;
		else
			color = BLUE;
		bold_line(s->walls[i].v1, s->walls[i].v2, ed, color);
		i++;
	}
}

void		render_manager(t_sdl *sdl, t_ed *ed)
{
	t_bool	end;

	init_render(ed);
	end = false;
	while (!end)
	{
		listen_controls(&end, ed);
		nice_grid(ed);
		render_map(ed);
		draw_info(ed);
		draw_selection(ed);
		sdl_apply_renderer(sdl, ed);
		if (ed->selection.sector != -1)
		{
			render_monsters(ed, sdl);
			render_sprites(ed, sdl);
			render_picker(ed, sdl);
		}
		SDL_RenderPresent(sdl->renderer);
		sdl_clear_texture(&(ed->pixels));
	}
	SDL_Delay(2000);
	SDL_Quit();
}
