
#include "editor.h"

void		clear_list(t_data *d)
{
	if (!d->monsters)
		return ;
	free(d->monsters);
	d->monsters = NULL;
}

int			fill_monster_structure(t_data *d)
{
	t_monster_list	*lst;
	int				i;

	clear_list(d);
	if (d->nbmonsters <= 0)
		return (0);
	if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) * d->nbmonsters)))
		return (printf("Failed to malloc monsters structure.\n"));
	lst = d->interface.monster_list->begin;
	i = 0;
	while (lst)
	{
		d->monsters[i] = (t_monster){lst->pos, {0.0, 0.0}, 0,
			lst->sectnunm, lst->selected_asset, 0, 0, 0, 1, 0, 0};
		lst = lst->next;
		i++;
	}
	return (0);
}

int			write_monster_data(t_data *d, int f)
{
	int	i;

	if (write(f, &d->nbmonsters, sizeof(uint16_t)) < 0)
		return (printf("Failed to write nummonsters.\n"));
	if (d->nbmonsters > 0)
	{
		if (fill_monster_structure(d))
			return (1);
		i = -1;
		while (++i < d->nbmonsters)
		{
			if (write(f, &d->monsters[i], sizeof(t_monster)) < 0)
				return (printf("Failed to write monsters.\n"));
		}
	}
	return (0);
}

static int	write_anim_texture(SDL_Surface **s, int f, int nb_anim)
{
	int		i;

	i = -1;
	while (++i < nb_anim)
	{
		if (write(f, &s[i]->w, sizeof(int)) < 0 ||
			write(f, &s[i]->h, sizeof(int)) < 0 ||
			write(f, s[i]->pixels, s[i]->w * s[i]->h * 4) < 0)
			return (printf("Failed to write animation size or texture.\n"));
	}
	return (0);
}

/*
**	i = monster_type_id
*/

int			write_monster_texture(t_data *d, int f, t_monsters_texture *mt)
{
	int		i;
	int		w;
	int		h;

	i = -1;
	while (++i < d->interface.nb_asset[1])
	{
		if (write(f, &mt[i].nb_walk_orientation, sizeof(int)) < 0 ||
			write_anim_texture(mt[i].walk, f, mt[i].nb_walk_anim) ||
			write_anim_texture(mt[i].attack, f, mt[i].nb_attack_anim) ||
			write(f, &mt[i].nb_death_anim, sizeof(int)) < 0 ||
			write_anim_texture(mt[i].death, f, mt[i].nb_death_anim))
			return (1);
	}
	i = -1;
	while (++i < 5)
	{
		w = d->projectile_monster[i]->w;
		h = d->projectile_monster[i]->h;
		if (write(f, &w, sizeof(int)) < 0 || write(f, &h, sizeof(int)) < 0 ||
			write(f, d->projectile_monster[i]->pixels, w * h * 4) < 0)
			return (printf("Failed to write animation size or texture.\n"));
	}
	return (0);
}
