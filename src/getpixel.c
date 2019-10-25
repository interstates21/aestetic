/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:55:39 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/25 22:33:26 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

uint32_t	pixel_pls_4_three(SDL_Surface *s, int x, double y, int mode)
{
	if (mode == 3)
	{
		y -= floor(y);
		return (s->userdata ?
			(((uint32_t*)s->pixels)[x + (int)(s->w *
				(y + ((intptr_t)s->userdata - 1))) * s->w]) :
			(((uint32_t*)s->pixels)[x + (int)(s->h * y) * s->w]));
	}
	return (0);
}

uint32_t	pixel_pls(SDL_Surface *s, double x, double y, int mode)
{
	t_vec2	real;

	if (mode == 0)
	{
		real.x = s->w * x;
		real.y = s->h * y;
		if (real.x >= 0 && real.y >= 0 && real.x < s->w && real.y < s->h)
			return (((uint32_t*)s->pixels)[real.x + real.y * s->w]);
	}
	else if (mode == 1)
	{
		real.x = s->w * (x - floor(x));
		y -= floor(y);
		if (s->userdata)
		{
			real.y = s->w * (y + ((intptr_t)s->userdata - 1));
			return (((uint32_t*)s->pixels)[real.x + real.y * s->w]);
		}
		real.y = s->h * y;
		return (((uint32_t*)s->pixels)[real.x + real.y * s->w]);
	}
	else if (mode == 2)
		return (((uint32_t*)s->pixels)[(short)x + (short)y * s->w]);
	return (pixel_pls_4_three(s, x, y, mode));
}
