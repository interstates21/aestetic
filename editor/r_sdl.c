/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_sdl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:40:35 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:40:36 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

Uint32		*get_screen_pixels(void)
{
	Uint32	*pixels;

	if (!(pixels = (Uint32 *)malloc(ED_W * ED_H * sizeof(Uint32))))
		print_err("allocating pixels failed.");
	memset(pixels, 0, ED_W * ED_H * sizeof(Uint32));
	return (pixels);
}

void		sdl_apply_renderer(t_sdl *sdl, t_ed *ed)
{
	SDL_RenderClear(sdl->renderer);
	SDL_UpdateTexture(sdl->texture, NULL, ed->pixels, ED_W * sizeof(Uint32));
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
}

void		sdl_put_pix(Uint32 **pixels, int x, int y, Uint32 color)
{
	if (x < 0 || y < 0 || x > ED_W - 1 || y > ED_H - 1)
		return ;
	(*pixels)[x + (y * ED_W)] = color;
}
