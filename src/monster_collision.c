#include "../includes/doom_nukem.h"


t_vec3f	update_pos_vec3f(t_vec3f new_pos, t_vec2f point, double radius)
{
	t_vec2f		tmp[2];

	tmp[0] = (t_vec2f){ new_pos.x - point.x, new_pos.z - point.y };
	tmp[1] = (t_vec2f){ radius, 0.0 };
	actualize_dir(atan2(tmp[0].y, tmp[0].x), &tmp[1]);
	return ((t_vec3f){ tmp[1].x + point.x, new_pos.y ,tmp[1].y + point.y });
}

t_vec2f	update_pos_vec2f(t_vec2f pos, t_vec2f point)
{
	t_vec2f		tmp;

	tmp = v2_min(pos, point);
	tmp = (t_vec2f){ 0.0, MINIMUM_SIZE_AROUND_MONSTERS };
	actualize_dir( atan2(tmp.y, tmp.x), &tmp);
	return (v2_plus(point, tmp));
}

void	collision_monster_monster(t_data *d, short cur_sect, t_monster *monster)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide &&
				&d->monsters[tmp->id] != monster)
			if (v2_len(v2_min(d->monsters[tmp->id].pos, monster->pos))
					< MINIMUM_SIZE_AROUND_MONSTERS)
				monster->pos = update_pos_vec2f(monster->pos,
						d->monsters[tmp->id].pos);
		tmp = tmp->next;
	}
}

void	collision_with_monster(t_data *d, short cur_sect)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
		{
			if (v2_len(v2_min(d->monsters[tmp->id].pos,
							(t_vec2f){d->cam.pos.x, d->cam.pos.z})) <
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius
					+ MONSTER_MIN_DIST_HITBOX && d->cam.pos.y <
					get_floceiheight(d, cur_sect, d->monsters[tmp->id].pos, 1)
					+ d->monster_type[d->monsters[tmp->id].id_type].height)
			{
				d->cam.pos = update_pos_vec3f(d->cam.pos, d->monsters
						[tmp->id].pos, d->monster_type[d->monsters[tmp->id].
						id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX);
				player_contact_monster(d, &(d->monsters[tmp->id]));
			}
		}
		tmp = tmp->next;
	}
}
