/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_bold_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 02:26:49 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 02:31:23 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	put_pixs(t_ed *ed, int x, int y)
{
	sdl_put_pix(&(ed->pixels), x, y, ed->color);
	sdl_put_pix(&(ed->pixels), x + 1, y + 1, ed->color);
	sdl_put_pix(&(ed->pixels), x - 1, y - 1, ed->color);
}

void	step_diff_fun11(t_v2 step_xy, t_v2 dx_y, t_v2 p1, t_ed *ed)
{
	int	i;
	int	step_diff;
	int	x;
	int y;

	step_diff = (dx_y.y << 1) - dx_y.x;
	x = p1.x + step_xy.x;
	y = p1.y;
	i = 1;
	put_pixs(ed, x, y);
	while (i <= dx_y.x)
	{
		if (step_diff > 0)
		{
			step_diff += (dx_y.y - dx_y.x) << 1;
			y += step_xy.y;
		}
		else
			step_diff += dx_y.y << 1;
		put_pixs(ed, x, y);
		i++;
		x += step_xy.x;
	}
}

void	step_diff_fun22(t_v2 step_xy, t_v2 dx_y, t_v2 p1, t_ed *ed)
{
	int	i;
	int	step_diff;
	int	x;
	int y;

	step_diff = (dx_y.x << 1) - dx_y.y;
	x = p1.x;
	y = p1.y + step_xy.y;
	i = 1;
	put_pixs(ed, x, y);
	while (i <= dx_y.y)
	{
		if (step_diff > 0)
		{
			step_diff += (dx_y.x - dx_y.y) << 1;
			x += step_xy.x;
		}
		else
			step_diff += dx_y.x << 1;
		put_pixs(ed, x, y);
		i++;
		y += step_xy.y;
	}
}

void	bold_line(t_v2 p1, t_v2 p2, t_ed *ed, Uint32 color)
{
	int dx;
	int dy;
	int step_x;
	int step_y;

	dx = abs(p2.x - p1.x);
	dy = abs(p2.y - p1.y);
	step_x = p2.x >= p1.x ? 1 : -1;
	step_y = p2.y >= p1.y ? 1 : -1;
	ed->color = color;
	if (dx > dy)
		step_diff_fun11((t_v2){step_x, step_y}, (t_v2){dx, dy}, p1, ed);
	else
		step_diff_fun22((t_v2){step_x, step_y}, (t_v2){dx, dy}, p1, ed);
}
