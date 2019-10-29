/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monsters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:29:34 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:54:00 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void			fetch_f(struct dirent *data, char *f, t_ed *e)
{
	char			*p;
	int				flag;

	if (ft_strequ(data->d_name, "walk") && (flag = A_WALK))
		p = ft_strjoin(f, "/walk/");
	else if (ft_strequ(data->d_name, "attack") && !(flag = A_ATTACK))
		p = ft_strjoin(f, "/attack/");
	else if (ft_strequ(data->d_name, "death") && (flag = A_DIE))
		p = ft_strjoin(f, "/death/");
	else
		return ;
	load_names(e, p, flag);
	free(p);
}

static void			get_files(t_ed *e, int type, char *name)
{
	DIR				*dir;
	struct dirent	*data;
	char			*f;

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
	int				i;
	char			*tmp[2];

	tmp[0] = "../texts/objects/monsters/motherdemon/anim_rots/";
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

void				init_monsters(t_ed *e)
{
	char			*names[M_TOTAL];
	int				i;

	names[M_RANGE] = M_NAME_1;
	names[M_MELEE] = M_NAME_2;
	i = -1;
	while (++i < M_TOTAL)
		get_files(e, i, names[i]);
	get_ranged_files(e);
}
