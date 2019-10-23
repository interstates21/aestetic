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
	d->slot1 = NULL;
	d->slot2 = NULL;
	d->slot3 = NULL;
	d->weapon_type.current_ammo = MAX_BULLETS;
}

void	init_player(t_data *d, t_player *player)
{
	(void)d;
	ft_bzero(player, sizeof(*player));
	player->current_weapon = CRYO_BALLISTA;
	player->speed_anim[CRYO_BALLISTA] = 4;
	player->weapon_anim[CRYO_BALLISTA][0] = 0;
	player->weapon_anim[CRYO_BALLISTA][1] = 2;
	player->weapon_anim[CRYO_BALLISTA][2] = 3;
	player->weapon_anim[CRYO_BALLISTA][3] = 4;
	player->weapon_anim[CRYO_BALLISTA][4] = 5;
	player->weapon_anim[CRYO_BALLISTA][5] = 6;
	player->weapon_anim[CRYO_BALLISTA][6] = 7;
	player->weapon_anim[CRYO_BALLISTA][7] = 8;
	player->weapon_anim[CRYO_BALLISTA][8] = 9;
	player->weapon_anim[CRYO_BALLISTA][9] = 10;
	player->weapon_anim[CRYO_BALLISTA][10] = 11;
	player->weapon_anim[CRYO_BALLISTA][11] = 12;
	player->weapon_anim[CRYO_BALLISTA][12] = 0;
	init_player_2(d, player);
}
