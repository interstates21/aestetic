#include "../includes/doom_nukem.h"

void	set_projectile_id(t_data *d, short i, short id_of_proj_type)
{
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = id_of_proj_type;
	d->projectiles[i].dir.z = d->cam.cos *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.y = d->cam.y_offset *
		Y_OFFSET_TO_ROT * d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.x = d->cam.sin *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].current_anim_playing =
		d->projectile_type[id_of_proj_type].anim_order[0];
	d->projectiles[i].pos = d->cam.pos;
	d->projectiles[i].has_collided = false;
	d->projectiles[i].cursectnum = d->cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].weapon_id = d->player.current_weapon;
	d->projectiles[i].target = NULL;
}

void	create_projectile(t_data *d, short id_of_proj_type)
{
	t_sprite_list	*new_projectile;
	short			i;

	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ;
	new_projectile = pure_malloc(sizeof(*new_projectile),
										"Cannot alloc projectiles");
	new_projectile->next = d->sectors[d->cursectnum].sprite_list;
	new_projectile->type = IS_PROJECTILE;
	new_projectile->id = i;
	set_projectile_id(d, i, id_of_proj_type);
	d->sectors[d->cursectnum].sprite_list = new_projectile;
}

void	set_projectile_id_monster(t_data *d, short i,
		short id_of_proj_type, t_monster *monster)
{
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = id_of_proj_type;
	d->projectiles[i].pos = (t_vec3f){
		monster->pos.x,
		d->sectors[monster->cursectnum].floorheight + 0.8,
		monster->pos.y};
	d->projectiles[i].dir.z = sin(monster->rot) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.y = (d->cam.pos.y -
			(d->sectors[monster->cursectnum].floorheight + 0.8)) /
		vec3f_length(v3_min(d->projectiles[i].pos, d->cam.pos)) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.x = cos(monster->rot) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].current_anim_playing =
		d->projectile_type[id_of_proj_type].anim_order[0];
	d->projectiles[i].has_collided = false;
	d->projectiles[i].weapon_id = d->monster_type[monster->id_type].id_of_proj;
	d->projectiles[i].cursectnum = monster->cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].target = NULL;
}

void	create_projectile_monster(t_data *d, short id_of_proj_type,
		t_monster *monster)
{
	t_sprite_list	*new_projectile;
	short			i;

	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ;
	new_projectile = pure_malloc(sizeof(*new_projectile), "Malloc Error");
	new_projectile->next = d->sectors[monster->cursectnum].sprite_list;
	new_projectile->type = IS_PROJECTILE;
	new_projectile->id = i;
	set_projectile_id_monster(d, i, id_of_proj_type, monster);
	d->sectors[monster->cursectnum].sprite_list = new_projectile;
}
