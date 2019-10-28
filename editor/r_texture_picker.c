/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture_picker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:56:09 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:56:10 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		render_map(t_ed *ed)
{
	int		i;
	t_v2	sv;

	i = -1;
	while (++i < ed->n_sect)
		render_sector(ed, &ed->seclist[i]);
	i = -1;
	while (++i < ed->n_walls)
		bold_line(ed->walls[i].v1, ed->walls[i].v2, ed, GRN);
	if (ed->selection.selected_vertex)
	{
		sv = *ed->selection.selected_vertex;
		circle(ed, new_v2(sv.x, sv.y), 10, 0xffff55);
	}
}

void		draw_mouse_highlight(t_ed *ed, t_v2 mouse)
{
	int		i;
	int		j;
	int		size;

	size = 8;
	i = -size;
	while (i < size)
	{
		j = -size;
		while (j < size)
		{
			sdl_put_pix(&(ed->pixels), mouse.x + j, mouse.y + i, 0xffff66);
			j++;
		}
		i++;
	}
}

void		draw_selection(t_ed *ed)
{
	int		offset;

	if (ed->selection.sprite == -1 && ed->selection.monster == -1)
		return ;
	draw_mouse_highlight(ed, ed->controller.mouse);
	if (ed->selection.sprite != -1)
	{
		offset = ed->selection.sprite * 36;
		circle(ed, new_v2(FIRST_SPRITE_W + offset,
		FIRST_SPRITE_H), 28, 0xff00ff);
	}
	if (ed->selection.monster == 0)
	{
		circle(ed, new_v2(MOSTER_1_PICKER_W, MOSTER_PICKER_H), 65, 0xff00ff);
	}
	else if (ed->selection.monster == 1)
	{
		circle(ed, new_v2(MOSTER_2_PICKER_W, MOSTER_PICKER_H), 65, 0xff00ff);
	}
}

void		render_texture_picker(t_ed *ed)
{
	int		i;
	int		j;
	t_v2	pos;

	i = 0;
	pos = new_v2(ED_W - 150, ED_H - 150);
	while (i < PICKER_SIZE)
	{
		j = 0;
		while (j < PICKER_SIZE)
		{
			j++;
			sdl_put_pix(&(ed->pixels), pos.x + i, pos.y + j, 0);
		}
		i++;
	}
}
