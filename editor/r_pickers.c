/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pickers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vslutiak <vslutiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:36:57 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 22:14:26 by vslutiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	init_texure_picker_rect(SDL_Rect *s, SDL_Rect *d, t_v2 p, int sz)
{
	s->x = 0;
	s->y = 0;
	s->w = sz;
	s->h = sz;
	d->x = ED_W - p.x / 2 - sz / 2;
	d->y = ED_H - p.y / 2 - sz / 2;
	d->w = sz;
	d->h = sz;
}

void		render_picker(t_ed *ed, t_sdl *sdl)
{
	SDL_Rect	s;
	SDL_Rect	d;
	SDL_Texture *picker_tex;

	if (ed->texture_picker)
	{
		picker_tex = SDL_CreateTextureFromSurface(sdl->renderer,
		ed->texture_picker);
		init_texure_picker_rect(&s, &d, new_v2(200, 200), SHAPE_SIZE);
		SDL_RenderCopy(sdl->renderer, picker_tex, &s, &d);
	}
}

void		render_monsters(t_ed *ed, t_sdl *sdl)
{
	SDL_Rect	s;
	SDL_Rect	d;
	SDL_Texture *tex;

	tex = SDL_CreateTextureFromSurface(sdl->renderer,
	ed->monster[0].acting[1][0]);
	init_texure_picker_rect(&s, &d, new_v2(180, 500), 100);
	SDL_RenderCopy(sdl->renderer, tex, &s, &d);
	tex = SDL_CreateTextureFromSurface(sdl->renderer,
	ed->monster[1].acting[0][0]);
	init_texure_picker_rect(&s, &d, new_v2(400, 500), 100);
	SDL_RenderCopy(sdl->renderer, tex, &s, &d);
}

void		render_sprites(t_ed *ed, t_sdl *sdl)
{
	SDL_Rect	s;
	SDL_Rect	d;
	SDL_Texture *tex;
	int			i;
	int			offset;

	i = 0;
	offset = 0;
	while (i < ed->n_sprites)
	{
		tex = SDL_CreateTextureFromSurface(sdl->renderer,
		ed->sprites[i].texture);
		init_texure_picker_rect(&s, &d, new_v2(600 - offset, 700), 30);
		SDL_RenderCopy(sdl->renderer, tex, &s, &d);
		i++;
		offset += 80;
	}
}

int			pickers(t_ed *e)
{
	if (e->selection.sector == -1)
		return (0);
	if (picking_monster(e->controller.mouse) == 1)
	{
		ft_putendl("Picking monster one");
		e->selection.monster = 0;
		e->selection.sprite = -1;
		return (1);
	}
	else if (picking_monster(e->controller.mouse) == 2)
	{
		ft_putendl("Picking monster two");
		e->selection.monster = 1;
		return (1);
	}
	else if (picking_sprite(e->controller.mouse, e->n_sprites) != -1)
	{
		e->selection.sprite = picking_sprite(e->controller.mouse, e->n_sprites);
		ft_putstr("Picking sprite ");
		ft_putnbr(e->selection.sprite);
		ft_putchar('\n');
		e->selection.monster = -1;
		return (1);
	}
	return (0);
}
