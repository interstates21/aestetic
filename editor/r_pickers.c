/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pickers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:36:57 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:36:58 by akolomoi         ###   ########.fr       */
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

int			pickers(t_ed *ed)
{
	ed->selection.monster = -1;
	ed->selection.sprite = -1;
	if (ed->selection.sector == -1)
		return (0);
	if (picking_monster(ed->controller.mouse) == 1)
	{
		ed->selection.monster = 0;
		ed->selection.sprite = -1;
		return (1);
	}
	else if (picking_monster(ed->controller.mouse) == 2)
	{
		ed->selection.monster = 1;
		return (1);
	}
	else if (picking_sprite(ed->controller.mouse, ed->n_sprites) != -1)
	{
		ed->selection.sprite = picking_sprite(ed->controller.mouse,
		ed->n_sprites);
		ft_putnbr(ed->selection.sprite);
		ft_putchar('\n');
		ed->selection.monster = -1;
		return (1);
	}
	return (0);
}
