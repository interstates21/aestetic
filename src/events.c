/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:03:55 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 18:49:06 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	pick_up(t_env *d, t_objects *objects)
{
	if (v2_len(v2_min(v3_to_v2(d->cam.pos), objects->world_pos)) <
	1.5 && !objects->used && (objects->is_interactive || objects->is_autopick
			|| objects->is_key || objects->is_jetpack))
	{
		use_asset(d, objects);
		return (true);
	}
	return (false);
}

void	ev_keydown(t_env *d, SDL_KeyboardEvent event)
{
	int			i;
	t_objects	*objects;

	if (event.keysym.sym == SDLK_ESCAPE)
		print_and_quit(d, "ESC");
	if (event.keysym.sym == SDLK_e)
	{
		i = -1;
		while (d->objects_n && ++i < d->objects[d->this_sect][0].objects_n)
		{
			objects = &d->objects[d->this_sect][i];
			if (pick_up(d, objects))
				return ;
		}
		door_use(d, &d->sectors[d->this_sect]);
	}
}

void	ev_mot_mouse(t_env *d, SDL_MouseMotionEvent event)
{
	double	offset;
	double	rotation;

	if (SDL_GetRelativeMouseMode() == SDL_TRUE)
	{
		offset = event.yrel * MOUSE_SENSITIVTY * 0.5;
		rotation = event.xrel * MOUSE_SENSITIVTY * 0.001;
		d->cam.y_offset += offset;
		d->cam.y_offset = CLAMP(d->cam.y_offset, -MAX_Y_OFFSET, MAX_Y_OFFSET);
		d->cam.rot += rotation;
	}
}

void	ev_butt_mouse(t_env *d, SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		if (event.state == SDL_PRESSED)
			d->left_mouse_button = MOUSE_PRESSED;
		else
			d->left_mouse_button = MOUSE_RELEASED;
	}
}
