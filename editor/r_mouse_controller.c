/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_mouse_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:32:10 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/28 18:32:11 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

int			in_range(double t)
{
	return (t >= 0.0 && t <= 1.0);
}

int			intersects(t_v2 l[2], t_sect *s)
{
	double	det;
	double	tmp[2];
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (++i < s->n_walls)
	{
		det = (s->walls[i].v2.x - s->walls[i].v1.x) * (l[0].y - l[1].y) -
				(l[0].x - l[1].x) * (s->walls[i].v2.y - s->walls[i].v1.y);
		if (!det)
			return (0);
		tmp[0] = (s->walls[i].v1.y - s->walls[i].v2.y) *
		(l[0].x - s->walls[i].v1.x) + (s->walls[i].v2.x - s->walls[i].v1.x) *
		(l[0].y - s->walls[i].v1.y);
		tmp[1] = (l[0].y - l[1].y) * (l[0].x - s->walls[i].v1.x) +
		(l[1].x - l[0].x) * (l[0].y - s->walls[i].v1.y);
		if (in_range(tmp[0] / det) && in_range(tmp[1] / det))
			res += 1;
	}
	return (res);
}

char		in_sector(t_ed *e)
{
	int		i;
	t_v2	line[2];

	i = -1;
	while (++i < e->n_sect)
	{
		line[1] = new_v2(0, 0);
		line[0] = e->controller.mouse;
		if (intersects(line, &e->seclist[i]) & 1)
			return (i);
	}
	return (-1);
}

void		handle_left_click(t_ed *ed)
{
	int k;

	if (pickers(ed))
		return ;
	k = in_sector(ed);
	ed->selection.sector = k;
	if (ed->selection.drawing)
		loop_creation(ed);
	else
		corner_selected(ed);
}

int			mouse_controller(t_ed *ed, SDL_Event *event)
{
	SDL_GetMouseState(&(ed->controller.mouse.x), &(ed->controller.mouse.y));
	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		ed->controller.mouse_is_pressed = true;
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			handle_left_click(ed);
		}
		if (event->button.button == SDL_BUTTON_RIGHT)
			ft_putendl("right pressed");
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		ed->controller.mouse_is_pressed = false;
	}
	return (0);
}
