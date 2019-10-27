/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:03:55 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 20:58:12 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

bool	pick_up(t_data *d, t_assets *assets)
{
	if (v2_len(v2_min(v3_to_v2(d->cam.pos), assets->world_pos)) <
		1.5 && !assets->used && (assets->is_interactive || assets->is_autopick
									|| assets->is_key || assets->is_jetpack))
	{
		use_asset(d, assets);
		return (true);
	}
	return (false);
}

void	event_key_down(t_data *d, SDL_KeyboardEvent event)
{
	int			i;
	t_assets	*assets;

	if (event.keysym.sym == SDLK_ESCAPE)
		print_and_quit(d, "ESC");
	if (event.keysym.sym == SDLK_e)
	{
		i = -1;
		while (d->nb_assets && ++i < d->assets[d->cursectnum][0].nb_assets)
		{
			assets = &d->assets[d->cursectnum][i];
			if (pick_up(d, assets))
				return ;
		}
		door_use(d, &d->sectors[d->cursectnum]);
	}
}

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event)
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

void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		if (event.state == SDL_PRESSED)
			d->left_mouse_button = MOUSE_PRESSED;
		else
			d->left_mouse_button = MOUSE_RELEASED;
	}
}
