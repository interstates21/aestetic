#include "../includes/doom_nukem.h"

void	free_monsters_and_assets(t_data *d, int i)
{
	int	j;
	int	k;

	i = -1;
	while (++i < MAXTYPEMONSTERS && (j = -1))
	{
		while (++j < 10 && (k = -1))
			while (++k < MAXNBOFANIMATION)
			{
				if (d->monster_text[i][j][k])
					SDL_FreeSurface(d->monster_text[i][j][k]);
				d->monster_text[i][j][k] = NULL;
			}
		k = 9;
		while (++k < 19)
		{
			if (d->monster_text[i][k][0])
				SDL_FreeSurface(d->monster_text[i][k][0]);
			d->monster_text[i][k][0] = NULL;
		}
	}
	if (d->nb_assets_texture > 0 && (i = -1))
		while (++i < d->nb_assets_texture)
			SDL_FreeSurface(d->assets_texture[i]);
	free(d->assets_texture);
}

void	free_weapons(t_data *d)
{
	int			i;
	int			j;
	int			*nb_tex;
	int			*nb_projectiles;

	nb_tex = (int[3]){13, 15, 3};
	nb_projectiles = (int[3]){20, 5, 5};
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < nb_tex[i])
			SDL_FreeSurface(d->weapon_tex[i][j]);
		j = -1;
		while (++j < nb_projectiles[i])
			SDL_FreeSurface(d->projectile_tex[i][j]);
	}
}

void	free_everything(t_data *d)
{
	int	i;

	if (d->nummonsters > 0)
		free(d->monsters);
	if (d->nb_assets > 0 && (i = -1) != 0)
		while (++i < d->numsectors)
			free(d->assets[i]);
	if (d->nb_textures > 0 && (i = -1) != 0)
		while (++i < d->nb_textures)
			free(d->tex_name_list[i]);
	if ((intptr_t)d->posters > 0 && (i = -1) != 0)
	{
		while (++i < d->nb_posters)
			SDL_FreeSurface(d->posters[i]);
		free(d->posters);
	}
	free_weapons(d);
	free_monsters_and_assets(d, 0);
	free(d->tex_name_list);
	free(d->assets);
	d->tex_name_list = NULL;
	d->assets = NULL;
	system("leaks --quiet doom_nukem");
}

void	clear_sector_sprites(t_data *d, short i)
{
	t_sprite_list	*to_free;
	t_sprite_list	*tmp;

	to_free = d->sectors[i].sprite_list;
	d->sectors[i].sprite_list = NULL;
	while (to_free)
	{
		tmp = to_free->next;
		free(to_free);
		to_free = tmp;
	}
}

void	handle_finish(t_data *d)
{
	int i;

	i = -1;
	while (++i < d->nb_textures)
		SDL_FreeSurface(d->textures[i]);
	free(d->textures);
	d->textures = NULL;
	i = -1;
	while (++i < MAX_PROJECTILES)
		d->projectiles[i].is_active = false;
	i = -1;
	while (++i < d->numsectors)
		clear_sector_sprites(d, i);
	system("leaks --quiet doom_nukem");
	free_everything(d);
	exit(1);
}
