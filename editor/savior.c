/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savior.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 19:01:29 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/24 19:01:30 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static int	has_dir(char *p)
{
	char	*dst;
	int		i;

	dst = ft_strdup("../maps/");
	i = -1;
	while (++i < ft_strlen(dst) && i < ft_strlen(p))
		if (dst[i] != p[i])
		{
			free(dst);
			return (0);
		}
	return (1);
}

static void	save_sfx(t_ed *e, char *path)
{
	int		fd;
	int		count;
	uint8_t	*buf;

	fd = -1;
	reopen_fd(&fd, path);
	if (!(buf = malloc(MAX_SOUND)))
		print_err("sound_buf malloc failed");
	if ((count = read(fd, buf, MAX_SOUND)) < 0)
		print_err("reading sound file failed");
	else if (count >= MAX_SOUND)
		print_err("sound file is too big");
	if (write(e->fd, &count, sizeof(count)) < 0
	|| write(e->fd, buf, count) < 0)
		print_err("saving sound file failed");
	free(buf);
	close(fd);
}

static void	write_sfx(t_ed *e)
{
	save_sfx(e, "../sounds/music.wav");
	save_sfx(e, "../sounds/blaster.wav");
	save_sfx(e, "../sounds/cryo_bal.wav");
	save_sfx(e, "../sounds/m16.wav");
	save_sfx(e, "../sounds/explosion.wav");
	save_sfx(e, "../sounds/player_fell.wav");
	save_sfx(e, "../sounds/player_got_hit.wav");
	save_sfx(e, "../sounds/player_death.wav");
	save_sfx(e, "../sounds/charg_agro.wav");
	save_sfx(e, "../sounds/charg_damage.wav");
	save_sfx(e, "../sounds/charg_death.wav");
	save_sfx(e, "../sounds/mother_agro.wav");
	save_sfx(e, "../sounds/mother_attack.wav");
	save_sfx(e, "../sounds/mother_death.wav");
	save_sfx(e, "../sounds/blaster_2.wav");
	save_sfx(e, "../sounds/refill_ammo.wav");
	save_sfx(e, "../sounds/health_up.wav");
	save_sfx(e, "../sounds/door_open.wav");
	save_sfx(e, "../sounds/door_close.wav");
	save_sfx(e, "../sounds/the-pikachu-song.wav");
}

char		*add_path(char *p)
{
	int			l;
	char		*tmp;
	char		*t;
	char		flags[2];

	l = ft_strlen(p);
	tmp = NULL;
	flags[0] = (l > 7) ? ft_strequ(".DNMAP", &p[l - 6]) : 0;
	flags[1] = has_dir(p);
	if (!flags[0])
		tmp = ft_strjoin(p, ".DNMAP");
	t = tmp;
	if (!flags[1])
		tmp = ft_strjoin("../maps/", tmp ? tmp : p);
	if (t)
		free(t);
	return (tmp ? tmp : p);
}

void		save_world(t_ed *e, char *path)
{
	if (e->n_sect <= 0)
		print_err("cool story bob");
	e->path = add_path(path);
	if (((e->fd = open(e->path, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
	|| write(e->fd, &e->player, sizeof(t_v3)) < 0
	|| write(e->fd, &e->p_ang, sizeof(double)) < 0
	|| write(e->fd, &e->start, sizeof(uint16_t)) < 0
	|| write(e->fd, &e->path, MAX_NAME) < 0)
		perror("saving map failed");
	write_secors(e);
	write_monsters(e);
	write_sprites(e);
	write_tex_list(e);
	write_tex_data(e);
	write_posters(e);
	write_weapon(e);
	write_mons_tex(e);
	write_sprt_tex(e);
	write_sfx(e);
	close(e->fd);
	ft_putstr("Map ");
	ft_putstr(e->path);
	ft_putendl(" saved.");
}
