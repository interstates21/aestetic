/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render_shit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 22:07:30 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/28 22:32:52 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	draw_square(t_ed *ed, t_v2 c, int r, Uint32 col)
{
	int i;
	int j;

	i = -r;
	while (i < r)
	{
		j = -r;
		while (j < r)
		{
			sdl_put_pix(&(ed->pixels), c.x + j, c.y + i, col);
			j++;
		}
		i++;
	}
}

void	nice_grid(t_ed *ed)
{
	int	i;
	int	j;

	i = 0;
	while (i < ED_W)
	{
		j = 0;
		while (j < ED_H)
		{
			if (j % GRID_GAP && i % GRID_GAP)
				sdl_put_pix(&(ed->pixels), i, j, GRID_COL_1);
			else
				sdl_put_pix(&(ed->pixels), i, j, GRID_COL_2);
			j++;
		}
		i++;
	}
}
