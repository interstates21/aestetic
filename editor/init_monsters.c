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

static void			fetch_f(DIR *dir, struct dirent *data, char *f, t_ed *e)
{
	char 			**names;
	char 			*p;

	p = NULL;
	if (ft_strequ(data->d_name, "walk"))
		p = ft_strjoin(f, "/walk/");
	else if (ft_strequ(data->d_name, "attack"))
		p = ft_strjoin(f, "/attack/");
	else if (ft_strequ(data->d_name, "death"))
		p = ft_strjoin(f, "/death/");
	if (!p)
		print_err("dir not found");
	load_names(e, p, &names);
	load_anims(e, p, names);
}

static void			get_files(t_ed *e, int type, char *name)
{
	DIR				*dir;
	struct dirent	*data;
	char 			*f;

	dir = NULL;
	f = ft_strjoin(MONSTERS, name);
	reopen(&dir, f);
	while ((data = readdir(dir)))
		if (data->d_type == DT_DIR)
			fetch_f(dir, data, f, e);
	free(f);
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
}
