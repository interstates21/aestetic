#include "../includes/doom_nukem.h"

void	display_weapon(t_data *d, SDL_Surface *s, t_vec2f start, t_vec2f end)
{
	t_vec2f			scale;
	short			x;
	short			y;
	uint32_t		colo;

	scale.x = 100.0 / (end.x - start.x) * 0.01;
	scale.y = 100.0 / (end.y - start.y) * 0.01;
	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < MIN(HEIGHT, end.y))
		{
			colo = getpixel(s, scale.x *
					(x - start.x), scale.y * (y - start.y));
			colo = alpha(((uint32_t *)d->sdl.screen->pixels)
					[x + y * d->sdl.screen->w], colo);
			putpixel(d, x, y, colo);
			y++;
		}
		x++;
	}
}

void	draw_weapon(t_data *d)
{
	t_vec2f			start;
	t_vec2f			end;
	t_vec2f			tmp;
	SDL_Surface		*cur_img;

	if (!d->player.timer_anim_weap)
	{
		d->player.current_anim_playing = d->player.weapon_anim
		[d->player.current_weapon][d->player.current_anim_playing];
		d->player.timer_anim_weap =
			d->player.speed_anim[d->player.current_weapon];
	}
	cur_img = d->weapon_tex[d->player.current_weapon]
		[d->player.current_anim_playing];
	d->player.timer_anim_weap--;
	start.x = WIDTH * 0.5 + d->player.timer_change_weap * WIDTH * 0.003 -
	cur_img->w * 0.5 * SIZE_OF_WEAP;
	tmp = d->inertia;
	actualize_dir(d->cam.rot, &tmp);
	start.x -= tmp.x * 150;
	end.x = start.x + cur_img->w * SIZE_OF_WEAP;
	end.y = (HEIGHT + d->player.timer_change_weap *
		HEIGHT * 0.010 + MAX_INERTIA * 50) + tmp.y * 50;
	start.y = end.y - cur_img->h * SIZE_OF_WEAP;
	display_weapon(d, cur_img, start, end);
}
