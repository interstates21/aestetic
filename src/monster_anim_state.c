
#include "../includes/doom_nukem.h"

void	anim_id_0(t_monster *monster, t_monster_type *monster_type, t_data *d)
{
	monster->anim_time--;
	if (monster->anim_time)
		return ;
	monster->anim_state = monster_type[monster->
		id_type].anim_order[monster->anim_state];
	monster->anim_time = SPEED_ANIM;
	if (monster->anim_state == MOTHER_DEMON_ATTACK &&
			monster->anim_time == SPEED_ANIM)
	{
		create_projectile_monster(d, FIREBALL_1, monster);
		play_sound(d, MOTHER_ATK_SOUND, monster->pos);
	}
}

void	anim_id_1(t_monster *monster, t_monster_type *monster_type)
{
	monster->anim_time--;
	if (monster->anim_time)
		return ;
	monster->anim_state = monster_type[monster->
		id_type].anim_order[monster->anim_state];
	if (monster->anim_state < 4)
		monster->anim_time = SPEED_ANIM_CHARG;
	else
		monster->anim_time = SPEED_ANIM_CHOW;
}

void	monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d)
{
	if (monster->id_type == MOTHERDEMON)
		anim_id_0(monster, monster_type, d);
	if (monster->id_type == CHARGINGDEMON)
		anim_id_1(monster, monster_type);
}
