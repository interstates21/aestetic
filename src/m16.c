#include "../includes/doom_nukem.h"

static void		set_projectile_visual_collided_m16(t_data *d,
		short i, t_m16_inf inf)
{
	t_vec2f	tmp;

	tmp.x = inf.dist;
	tmp.y = 0.0;
	actualize_dir(d->cam.rot + M_PI, &tmp);
	tmp.x = d->cam.sin * inf.dist + d->cam.pos.x;
	tmp.y = d->cam.cos * inf.dist + d->cam.pos.z;
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = M16;
	d->projectiles[i].dir.z = 0.0;
	d->projectiles[i].dir.y = 0.0;
	d->projectiles[i].dir.x = 0.0;
	d->projectiles[i].current_anim_playing =
		d->projectile_type[M16].anim_order[0];
	d->projectiles[i].pos = (t_vec3f){tmp.x,
		inf.dist * Y_OFFSET_TO_ROT * d->cam.y_offset + d->cam.pos.y, tmp.y};
	d->projectiles[i].has_collided = true;
	d->projectiles[i].cursectnum =
		d->monsters[inf.id_of_monst].cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].weapon_id = d->player.current_weapon;
	d->projectiles[i].target = &d->monsters[inf.id_of_monst];
	d->projectiles[i].dir = v3_min(d->projectiles[i].pos, v2_to_v3(
				d->monsters[inf.id_of_monst].pos));
}

static void		m16_create_projectile(t_data *d, t_m16_inf inf)
{
	t_sprite_list	*new_projectile;
	short			i;

	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ;
	if (!(new_projectile = malloc(sizeof(*new_projectile))))
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_projectile->id = i;
	new_projectile->type = IS_PROJECTILE;
	set_projectile_visual_collided_m16(d, i, inf);
	{
		new_projectile->next = d->sectors[d->
			monsters[inf.id_of_monst].cursectnum].sprite_list;
		d->sectors[d->monsters[inf.id_of_monst].
			cursectnum].sprite_list = new_projectile;
	}
}

bool	set_pos_m16_inside_sec(t_data *d, int16_t id, t_vec2f *pos)
{
	*pos = d->monsters[id].pos;
	pos->x -= d->cam.pos.x;
	pos->y -= d->cam.pos.z;
	actualize_dir(d->cam.rot, pos);
	return (true);
}

void		m16_shoot(t_data *d)
{
	t_m16_inf	inf;
	double		y_dist;
	double		floor_height;
	int16_t		sectNum;
	t_vec2f		pos;


	sectNum = d->monsters[inf.id_of_monst].cursectnum;
	pos = d->monsters[inf.id_of_monst].pos;
	inf = m16_recur(d, d->cursectnum, -1);
	if (d->weapon_type[M16].current_ammo)
		d->weapon_type[M16].current_ammo--;
	if (inf.id_of_monst != -1)
	{
		floor_height = getFloorHeight(&d->sectors[sectNum], d->walls, sectNum, pos);
		y_dist = inf.dist * Y_OFFSET_TO_ROT * d->cam.y_offset +
			d->cam.pos.y - floor_height;
		if (y_dist > -0.1 && y_dist < 1.6)
		{
			monster_hit(d, M16_DAMAGE, inf.id_of_monst);
			inf.dist -= 0.1;
			m16_create_projectile(d, inf);
		}
	}
}

