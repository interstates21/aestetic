/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:17:19 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/29 22:54:47 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void		read_wp_proj(t_ed *e, char *p, const int params[3])
{
	int				i;
	char			*path;
	DIR				*dir;
	struct dirent	*data;

	path = ft_strjoin(p, "projectiles/");
	dir = NULL;
	reopen(&dir, path);
	i = 0;
	while (i < params[2] && (data = readdir(dir)))
		if (bmp_check(data))
		{
			e->weapon[params[0]][1][i] = ft_strjoin(path, data->d_name);
			i++;
		}
	closedir(dir);
	free(path);
}

static void		read_wp_list(t_ed *e, char *name, int params[3])
{
	int				i;
	char			*path;
	DIR				*dir;
	struct dirent	*data;

	path = ft_strjoin("../texts/objects/weapons/", name);
	dir = NULL;
	reopen(&dir, path);
	i = 0;
	while (i < params[1] && (data = readdir(dir)))
		if (bmp_check(data))
		{
			e->weapon[params[0]][0][i] = ft_strjoin(path, data->d_name);
			i++;
		}
	closedir(dir);
	if (params[2] > 0)
		read_wp_proj(e, path, params);
	free(path);
}

static void		sort_list(t_ed *e, int i, int n_tex[3], int n_p[3])
{
	char		*p;
	int			j;
	int			k;

	j = -1;
	while (++j < n_tex[i] - 1 && ((k = j) | 1))
		while (++k < n_tex[i] - 1)
			if (ft_strcmp(e->weapon[i][0][j], e->weapon[i][0][k]) > 0)
			{
				p = e->weapon[i][0][j];
				e->weapon[i][0][j] = e->weapon[i][0][k];
				e->weapon[i][0][k] = p;
			}
	j = -1;
	while (++j < n_p[i] - 1 && ((k = j) | 1))
		while (++k < n_p[i])
			if (ft_strcmp(e->weapon[i][1][j], e->weapon[i][1][k]) > 0)
			{
				p = e->weapon[i][1][j];
				e->weapon[i][1][j] = e->weapon[i][1][k];
				e->weapon[i][1][k] = p;
			}
}

static void		load_wp_list(t_ed *e, char *name[3], int n_tex[3], int n_p[3])
{
	int			i;

	i = -1;
	while (++i < 3)
		read_wp_list(e, name[i], (int[3]){i, n_tex[i], n_p[i]});
	i = -1;
	while (++i < 3)
		sort_list(e, i, n_tex, n_p);
}

void			write_weapon(t_ed *e)
{
	char		*str;

	str = ft_strdup(M_NAME_1);
	load_wp_list(e, (char*[]){"cryo_ballista/", "blaster/", "m16/"},
	(int[3]){13, 15, 3}, (int[3]){20, 0, 5});
	load_wp_tex(e, (int[3]){13, 15, 3}, (int[3]){20, 0, 5});
	write(e->fd, &str, ft_strlen(str));
	save_wp_tex(e, (int[3]){13, 15, 3}, (int[3]){20, 0, 5});
	free(str);
}
