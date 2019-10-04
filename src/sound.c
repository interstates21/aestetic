#include "../includes/doom_nukem.h"

void	play_sound(t_data *d, uint8_t id, t_vec2f pos)
{
	static uint8_t	i;
	int16_t			angle;
	uint8_t			dist;

	if (pos.x == d->cam.pos.x)
	{
		angle = 0;
		dist = ft_min(v2_len(v2_min(v3_to_v2(d->cam.pos), pos)), 254);
	}
	else
	{
		pos = v2_min(pos, v3_to_v2(d->cam.pos));
		actualize_dir(d->cam.rot, &pos);
		angle = -atan2(pos.y, pos.x) * 180 / M_PI + 90;
		dist = ft_min(v2_len(v2_min(v3_to_v2(d->cam.pos), pos)) * 4,
				254);
	}
	Mix_PlayChannel(i, d->chunk[id], 0);
	Mix_SetPosition(i, angle, dist);
	if (++i > 98)
		i = 0;
}

void	play_music(t_data *d, uint8_t id)
{
	if (id == 0 && Mix_Playing(99))
		return ;
	if (Mix_PlayChannel(99, d->chunk[id], -1) == -1)
		printf("play_music: %s\n", SDL_GetError());
}
