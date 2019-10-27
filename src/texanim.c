/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texanim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 05:39:26 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 05:40:33 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	precompute_texanim(t_data *d)
{
	int			i;
	SDL_Surface	*s;
	t_vec2		frames;

	frames.x = SDL_GetTicks() / 80;
	i = -1;
	while (++i < d->nb_textures)
	{
		s = d->textures[i];
		frames.y = s->h / s->w;
		if (frames.y <= 5)
			s->userdata = 0;
		else
			s->userdata = (void*)(intptr_t)(frames.x % frames.y + 1);
	}
}
