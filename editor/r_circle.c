/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_circle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:25:25 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:25:26 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	circle_pix(t_ed *ed, t_v2 c, t_v2 v, Uint32 color)
{
	sdl_put_pix(&(ed->pixels), c.x + v.x, c.y + v.y, color);
	sdl_put_pix(&(ed->pixels), c.x + v.x, c.y - v.y, color);
	sdl_put_pix(&(ed->pixels), c.x - v.x, c.y + v.y, color);
	sdl_put_pix(&(ed->pixels), c.x - v.x, c.y - v.y, color);
	sdl_put_pix(&(ed->pixels), c.x + v.y, c.y + v.x, color);
	sdl_put_pix(&(ed->pixels), c.x + v.y, c.y - v.x, color);
	sdl_put_pix(&(ed->pixels), c.x - v.y, c.y + v.x, color);
	sdl_put_pix(&(ed->pixels), c.x - v.y, c.y - v.x, color);
}

int			circle(t_ed *ed, t_v2 c, int r, Uint32 color)
{
	int		j;
	int		i;
	int		p;

	j = 0;
	i = r;
	p = 3 - 2 * r;
	circle_pix(ed, c, new_v2(j, i), color);
	while (j < i)
	{
		if (p < 0)
		{
			j++;
			p = p + 4 * j + 6;
		}
		else
		{
			j++;
			i--;
			p = p + 4 * (j - i) + 10;
		}
		circle_pix(ed, c, new_v2(j, i), color);
	}
	return (0);
}
