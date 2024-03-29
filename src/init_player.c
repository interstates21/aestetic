#include "../includes/doom_nukem.h"

void	init_player_2(t_data *d, t_player *player)
{
	d->color_buf.value = 0;
	player->is_flying = 0;
	player->minimum_height = MINIMUM_HEIGHT;
	player->gravity = 0.0;
	player->can_move = 0;
	player->health = 100;
	player->can_be_stomped = 0;
	d->cursectnum = d->startsectnum;
	d->cam = d->startcam;
	d->cam.rot += 0.001;
	d->slot2 = NULL;
	d->weapon_type.current_ammo = MAX_BULLETS;
}

void	init_player(t_data *d, t_player *player)
{
	int i;
	(void)d;

	i = 1;
	ft_bzero(player, sizeof(*player));
	player->current_weapon = CRYO_BALLISTA;
	player->speed_anim[CRYO_BALLISTA] = 4;
	player->weapon_anim[CRYO_BALLISTA][0] = 0;
	while (i < 12)
	{
		player->weapon_anim[CRYO_BALLISTA][i] = i + 1;
		i++;
	}
	player->weapon_anim[CRYO_BALLISTA][12] = 0;
	init_player_2(d, player);
}
