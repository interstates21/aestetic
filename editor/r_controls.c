/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_controls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:27:15 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:27:16 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void	rng(int *val, int big, int low, int inc)
{
	*val += inc;
	if (*val < low)
		*val = big;
	else if (*val > big)
		*val = low;
}

static void	sng(short *val, int big, int low, int inc)
{
	*val += inc;
	if (*val < low)
		*val = big;
	else if (*val > big)
		*val = low;
}

static void	pt2(t_ed *e, int inc)
{
	if (e->selection.select == E_FLOOR_TEX)
		sng(&e->seclist[e->selection.sector].tex[T_FLOOR],
		e->n_tex - 1, 0, inc);
	else if (e->selection.select == E_WALL_TEX)
		sng(&e->seclist[e->selection.sector].tex[T_WALL], e->n_tex - 1, 0, inc);
	else if (e->selection.select == E_CEIL_TEX)
		sng(&e->seclist[e->selection.sector].tex[T_CEIL], e->n_tex - 1, 0, inc);
	else if (e->selection.select == E_DANGER)
		e->seclist[e->selection.sector].is_dmg ^= 1;
	else if (e->selection.select == E_ELEVATOR)
		e->seclist[e->selection.sector].is_elev ^= 1;
	else if (e->selection.select == E_EXIT)
		e->seclist[e->selection.sector].is_finish ^= 1;
	else if (e->selection.select == E_FLOOR)
		sng(&e->seclist[e->selection.sector].height[H_FLOOR],
		e->seclist[e->selection.sector].height[H_CEIL] - 10, 0, inc);
}

static void	affect(t_ed *e, int inc)
{
	if (e->selection.select == E_SLOPE)
	{
		sng(&e->seclist[e->selection.sector].slope[H_FLOOR], 30, 0, inc);
		e->seclist[e->selection.sector].slope[H_CEIL] =
		e->seclist[e->selection.sector].slope[H_FLOOR];
	}
	else if (e->selection.select == E_SLOPE_ROT)
	{
		sng(&e->seclist[e->selection.sector].slope_rot[H_FLOOR],
		360, 0, inc * 15);
		e->seclist[e->selection.sector].slope_rot[H_CEIL] =
		e->seclist[e->selection.sector].slope_rot[H_FLOOR];
	}
	else if (e->selection.select == E_CEIL)
	{
		sng(&e->seclist[e->selection.sector].height[H_CEIL], 200, 20, inc);
		if (e->seclist[e->selection.sector].height[H_CEIL] - 10 <=
		e->seclist[e->selection.sector].height[H_FLOOR])
			sng(&e->seclist[e->selection.sector].height[H_FLOOR],
			e->seclist[e->selection.sector].height[H_CEIL] - 10, 0, inc);
	}
	else
		pt2(e, inc);
}

void		listen_controls(t_bool *end, t_ed *ed)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			*end = true;
		mouse_controller(ed, &event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
				affect(ed, -1);
			if (event.key.keysym.sym == SDLK_RIGHT)
				affect(ed, 1);
		}
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				*end = true;
			if (event.key.keysym.sym == SDLK_UP)
				rng(&ed->selection.select, 11, 2, -1);
			if (event.key.keysym.sym == SDLK_DOWN)
				rng(&ed->selection.select, 11, 2, 1);
		}
	}
}
