/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:29:34 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 18:29:35 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void			load_anims(t_ed *e, char *p, char **names, int flag)
{
	int 			i;
	char 			*f;

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

static void			fetch_f(struct dirent *data, char *f, t_ed *e)
{
	char 			**names;
	char 			*p;
	int 			flag;

	p = NULL;
	if (ft_strequ(data->d_name, "walk") && (flag = A_WALK))
		p = ft_strjoin(f, "/walk/");
	else if (ft_strequ(data->d_name, "attack") && !(flag = A_ATTACK))
		p = ft_strjoin(f, "/attack/");
	else if (ft_strequ(data->d_name, "death") && (flag = A_DIE))
		p = ft_strjoin(f, "/death/");
	if (!p)
		print_err("dir not found");
	load_names(e, p, &names, flag);
	load_anims(e, p, names, flag);
	free(names);
	free(p);
}

static void			get_files(t_ed *e, int type, char *name)
{
	DIR				*dir;
	struct dirent	*data;
	char 			*f;

	dir = NULL;
	e->curr_m = type;
	f = ft_strjoin(MONSTERS, name);
	reopen(&dir, f);
	while ((data = readdir(dir)))
		if (data->d_type == DT_DIR)
			fetch_f(data, f, e);
	free(f);
	closedir(dir);
}

static void			get_ranged_files(t_ed *e)
{
	DIR				*dir;
	struct dirent	*data;
	int 			i;
	char 			*tmp[2];

	tmp[0] = "../textures/assets/monsters/motherdemon/projectiles/";
	dir = NULL;
	reopen(&dir, tmp[0]);
	i = 0;
	while ((data = readdir(dir)))
		if (bmp_check(data))
		{
			tmp[1] = ft_strjoin(tmp[0], data->d_name);
			read_bmp(&e->m_projec[i++], tmp[1]);
			free(tmp[1]);
		}
	closedir(dir);
}

void 				init_monsters(t_ed *e)
{
	char 			*names[M_TOTAL];
	int 			i;

	names[M_RANGE] = M_NAME_1;
	names[M_MELEE] = M_NAME_2;
	i = -1;
	while (++i < M_TOTAL)
		get_files(e, i, names[i]);
	get_ranged_files(e);
}
