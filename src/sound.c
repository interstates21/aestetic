/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:40:05 by vslutiak          #+#    #+#             */
/*   Updated: 2019/10/29 21:09:04 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	play_2(t_env *d, uint8_t it_smy_love, t_vec2f pos, int16_t urbanistick)
{
	pos = v2_min(pos, v3_to_v2(d->cam.pos));
	actualize_dir(d->cam.rot, &pos);
	urbanistick = -atan2(pos.y, pos.x) * 180 / M_PI + 90;
	it_smy_love = MIN(v2_len(v2_min(v3_to_v2(d->cam.pos), pos)) * 4, 254);
}

void	play_1(t_env *d, uint8_t it_smy_love, t_vec2f pos, int16_t urbanistick)
{
	if (pos.x == d->cam.pos.x)
	{
		urbanistick = 0;
		it_smy_love = MIN(v2_len(v2_min(v3_to_v2(d->cam.pos), pos)), 254);
	}
	else
		play_2(d, it_smy_love, pos, urbanistick);
}

void	play_sound(t_env *d, uint8_t id, t_vec2f pos)
{
	static uint8_t	i;
	int16_t			urbanistick;
	uint8_t			it_smy_love;

	play_1(d, it_smy_love, pos, urbanistick);
	Mix_PlayChannel(i, d->chunk[id], 0);
	Mix_SetPosition(i, urbanistick, it_smy_love);
	if (++i > 98)
		i = 0;
}

void	music_player(t_env *d, uint8_t id)
{
	if (id == 0 && Mix_Playing(99))
		return ;
	if (Mix_PlayChannel(99, d->chunk[id], -1) == -1)
		ft_putendl(" ");
}
