#include "../includes/doom_nukem.h"

void	handle_sound_shot(t_data *d)
{
	if (d->player.current_weapon == BLASTER)
		play_sound(d, BLASTER_SOUND, v3_to_v2(d->cam.pos));
	if (d->player.current_weapon == CRYO_BALLISTA)
		play_sound(d, CRYO_SOUND, v3_to_v2(d->cam.pos));
}

void	shoot_weapon(t_data *d, uint8_t *w)
{
	if (d->left_mouse_button == MOUSE_PRESSED)
	{
		d->player.timer_anim_weap = d->player.speed_anim[*w];
		d->player.current_anim_playing = 1;
		d->player.can_shoot = d->weapon_type[*w].rate_of_fire[0];
		d->player.click = LEFT_CLICK;
		handle_sound_shot(d);
	}
	else if (d->right_mouse_button == MOUSE_PRESSED &&
			d->weapon_type[*w].has_alt_fire && d->weapon_type
			[d->player.current_weapon].current_ammo > 1)
	{
		d->player.can_shoot = d->weapon_type[*w].rate_of_fire[1];
		d->player.timer_anim_weap = d->player.speed_anim[*w];
		d->player.current_anim_playing = 1;
		d->player.click = RIGHT_CLICK;
		play_sound(d, BLASTER_2_SOUND, v3_to_v2(d->cam.pos));
	}
}

void	player_actions(t_data *d)
{
	uint8_t	*w;

	w = &d->player.current_weapon;
	if (d->player.can_shoot)
		d->player.can_shoot--;
	else if (d->weapon_type[d->player.current_weapon].current_ammo)
		shoot_weapon(d, w);
	if (d->left_mouse_button == MOUSE_PRESSED && !d->weapon_type[d->player.
			current_weapon].current_ammo)
		invoke_msg(d, "Out of ammo !!");
	if (*w == CRYO_BALLISTA && d->player.current_anim_playing == 5
			&& !d->player.timer_anim_weap)
	{
		if (d->weapon_type[CRYO_BALLISTA].current_ammo)
			d->weapon_type[CRYO_BALLISTA].current_ammo--;
		create_projectile(d, d->weapon_type[*w].left_projectile);
	}
	if (*w == BLASTER && d->player.current_anim_playing == 11
			&& !d->player.timer_anim_weap)
		blaster_shot(d);
}
