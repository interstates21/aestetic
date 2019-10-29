/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 03:12:36 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/28 18:28:16 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

static void	circle_pix(t_env *e, t_vec2 c, t_vec2 v, Uint32 color)
{
	pixel_put(e, new_v3(c.x + v.x, c.y + v.y, 0), color, 0);
	pixel_put(e, new_v3(c.x - v.x, c.y - v.y, 0), color, 0);
	pixel_put(e, new_v3(c.x + v.x, c.y - v.y, 0), color, 0);
	pixel_put(e, new_v3(c.x - v.x, c.y + v.y, 0), color, 0);
	pixel_put(e, new_v3(c.x + v.y, c.y + v.x, 0), color, 0);
	pixel_put(e, new_v3(c.x + v.y, c.y - v.x, 0), color, 0);
	pixel_put(e, new_v3(c.x - v.y, c.y + v.x, 0), color, 0);
	pixel_put(e, new_v3(c.x - v.y, c.y - v.x, 0), color, 0);
}

int			circle(t_env *e, t_vec2 c, int r, Uint32 color)
{
	int	j;
	int	i;
	int	p;

	j = 0;
	i = r;
	p = 3 - 2 * r;
	circle_pix(e, c, new_v2int(j, i), color);
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
		circle_pix(e, c, new_v2int(j, i), color);
	}
	return (0);
}
