#include "../includes/doom_nukem.h"

void	init_projectiles_type_cryo_bow2(t_data *d)
{
	d->projectile_type[CRYO_BALLISTA].anim_order[11] = 12;
	d->projectile_type[CRYO_BALLISTA].anim_order[12] = 13;
	d->projectile_type[CRYO_BALLISTA].anim_order[13] = 14;
	d->projectile_type[CRYO_BALLISTA].anim_order[14] = 15;
	d->projectile_type[CRYO_BALLISTA].anim_order[15] = 16;
	d->projectile_type[CRYO_BALLISTA].anim_order[16] = 17;
	d->projectile_type[CRYO_BALLISTA].anim_order[17] = 18;
	d->projectile_type[CRYO_BALLISTA].anim_order[18] = 19;
	d->projectile_type[CRYO_BALLISTA].anim_order[19] = MUST_BE_DESTROYED;
	d->projectile_type[CRYO_BALLISTA].anim_order[COLLISION_ID] = 7;
	d->projectile_type[CRYO_BALLISTA].size = 1.5;
}

void	init_projectiles_type_cryo_bow(t_data *d)
{
	d->projectile_type[CRYO_BALLISTA].threat_to_player = false;
	d->projectile_type[CRYO_BALLISTA].threat_to_monster = true;
	d->projectile_type[CRYO_BALLISTA].hitbox_radius = 0.1;
	d->projectile_type[CRYO_BALLISTA].speed = 0.25;
	d->projectile_type[CRYO_BALLISTA].damage = 80;
	d->projectile_type[CRYO_BALLISTA].anim_order[0] = 1;
	d->projectile_type[CRYO_BALLISTA].anim_order[1] = 2;
	d->projectile_type[CRYO_BALLISTA].anim_order[2] = 3;
	d->projectile_type[CRYO_BALLISTA].anim_order[3] = 4;
	d->projectile_type[CRYO_BALLISTA].anim_order[4] = 5;
	d->projectile_type[CRYO_BALLISTA].anim_order[5] = 6;
	d->projectile_type[CRYO_BALLISTA].anim_order[6] = 6;
	d->projectile_type[CRYO_BALLISTA].anim_order[7] = 8;
	d->projectile_type[CRYO_BALLISTA].anim_order[8] = 9;
	d->projectile_type[CRYO_BALLISTA].anim_order[9] = 10;
	d->projectile_type[CRYO_BALLISTA].anim_order[10] = 11;
	init_projectiles_type_cryo_bow2(d);
}

void	init_projectiles_fireball_1(t_data *d)
{
	d->projectile_type[FIREBALL_1].threat_to_monster = false;
	d->projectile_type[FIREBALL_1].threat_to_player = true;
	d->projectile_type[FIREBALL_1].hitbox_radius = 0.5;
	d->projectile_type[FIREBALL_1].speed = 0.05;
	d->projectile_type[FIREBALL_1].damage = d->difficulty == HARD ? 20 : 15;
	d->projectile_type[FIREBALL_1].anim_order[0] = 1;
	d->projectile_type[FIREBALL_1].anim_order[1] = 0;
	d->projectile_type[FIREBALL_1].anim_order[COLLISION_ID] = 2;
	d->projectile_type[FIREBALL_1].anim_order[2] = 3;
	d->projectile_type[FIREBALL_1].anim_order[3] = 4;
	d->projectile_type[FIREBALL_1].anim_order[4] = MUST_BE_DESTROYED;
	d->projectile_type[FIREBALL_1].size = 12;
}

void	init_weapons(t_data *d)
{
	d->weapon_type.rate_of_fire[0] =
		d->player.speed_anim[CRYO_BALLISTA] * 11;
	d->weapon_type.has_alt_fire = false;
}

void	init_projectiles(t_data *d)
{
	ft_bzero(d->projectile_type, sizeof(t_proj_type) * MAX_KIND_OF_PROJECTILE);
	ft_bzero(d->projectiles, sizeof(t_projectile) * MAX_PROJECTILES);
	init_weapons(d);
	init_projectiles_type_cryo_bow(d);
	init_projectiles_fireball_1(d);
}
