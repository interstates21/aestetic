#include "../includes/doom_nukem.h"



void	shoot_weapon(t_data *d, uint8_t *w)
{
	if (d->left_mouse_button == MOUSE_PRESSED)
	{
		d->player.timer_anim_weap = d->player.speed_anim[*w];
		d->player.current_anim_playing = 1;
		d->player.can_shoot = d->weapon_type.rate_of_fire[0];
		d->player.click = LEFT_CLICK;
		play_sound(d, CRYO_SOUND, v3_to_v2(d->cam.pos));
	}
}

void	player_actions(t_data *d)
{
	uint8_t	*w;

	w = &d->player.current_weapon;
	if (d->player.can_shoot)
		d->player.can_shoot--;
	else if (d->weapon_type.current_ammo)
		shoot_weapon(d, w);
	if (d->left_mouse_button == MOUSE_PRESSED && !d->weapon_type.current_ammo)
		invoke_msg(d, "Out of ammo !!");
	if (d->player.current_anim_playing == 5 && !d->player.timer_anim_weap)
	{
		if (d->weapon_type.current_ammo)
			d->weapon_type.current_ammo--;
		create_projectile(d, d->weapon_type.left_projectile);
	}
}
