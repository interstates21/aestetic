/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_anims.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:13:08 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 19:13:10 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		get_rot(t_ed *e, int k, char **names, int t)
{
	int		i;
	int		tmp;
	int		rot;

	i = -1;
	rot = 1;
	while (++i < k)
	{
		tmp = names[i][ft_strchr(names[i], '.') - 1 - names[i]];
		if (!ft_isdigit(tmp))
			print_err("bad file name");
		rot = MAX(tmp - '0', rot);
	}
	if (k % rot)
		print_err("missing animation files");
	e->monster[e->curr_m].anim[t] = k;
	e->monster[e->curr_m].a_rot[t] = rot;
}

static void		load_anims(t_ed *e, char *p, char **names, int flag)
{
	int			i;
	char		*f;

	if (!(e->monster[e->curr_m].acting[flag] = (SDL_Surface**)malloc(
			sizeof(SDL_Surface*) * e->monster[e->curr_m].anim[flag])))
		print_err("malloc failed");
	i = -1;
	while (++i < e->monster[e->curr_m].anim[flag])
	{
		f = ft_strjoin(p, names[i]);
		read_bmp(&e->monster[e->curr_m].acting[flag][i], f);
		free(f);
		free(names[i]);
	}
}

void			load_names(t_ed *e, char *p, int i)
{
	DIR				*dir;
	struct dirent	*data;
	int				k;
	char			**names;

	dir = NULL;
	reopen(&dir, p);
	if (!(names = (char**)malloc(sizeof(char*) * 50)))
		print_err("malloc failed");
	k = 0;
	while ((data = readdir(dir)))
		if (bmp_check(data) && k < 49)
		{
			if (ft_strlen(data->d_name) > 10)
				print_err("animation file name is too long");
			names[k] = ft_strdup(data->d_name);
			k++;
		}
	closedir(dir);
	get_rot(e, k, names, i);
	load_anims(e, p, names, i);
	free(names);
}
