#include "../includes/doom_nukem.h"

void	invoke_msg(t_data *d, char *msg)
{
	if (ft_strlen(msg) > 99)
		return ((void)printf("msg is too long\n"));
	ft_strcpy(d->msg, msg);
	d->msg_start = SDL_GetTicks();
}


void	reset_assets(t_data *d)
{
	int i;
	int j;

	i = -1;
	while (d->nb_assets && ++i < d->numsectors)
	{
		j = -1;
		while (++j < d->assets[i][0].nb_assets)
			d->assets[i][j].used = false;
	}
}

void	handle_respawn(t_data *d)
{
	play_sound(d, PLAYER_DEATH_SOUND, v3_to_v2(d->cam.pos));
	init_monsters(d);
	init_player(d, &d->player);
	reset_assets(d);
	invoke_msg(d, "YOU DIED");
}
