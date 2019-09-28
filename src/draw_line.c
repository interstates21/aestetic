/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:25:07 by akolomoi          #+#    #+#             */
/*   Updated: 2019/09/28 16:25:09 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/alt.h"

void		draw_line(t_scene *s, t_scheme sc)
{
	int		y;

	sc.y1 = clamp(sc.y1, 0, HEIGHT - 1);
	sc.y2 = clamp(sc.y2, 0, HEIGHT - 1);
	if (sc.y2 == sc.y1)
		sdl_put_pix(&(s->pixels), sc.x, sc.y1, sc.mid);
	else if (sc.y2 > sc.y1)
	{
		sdl_put_pix(&(s->pixels), sc.x, sc.y1, sc.top);
		y = sc.y1;
		while (++y < sc.y2)
			sdl_put_pix(&(s->pixels), sc.x, y, sc.mid);
		sdl_put_pix(&(s->pixels), sc.x, sc.y2, sc.bot);
	}
}
