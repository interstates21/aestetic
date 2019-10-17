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

static void		get_rot(t_ed *e, int k, char ***names, int t)
{
	int 		i;
	int 		tmp;
	int 		rot;

	i = -1;
	rot = 1;
	while (++i < k)
	{
		tmp = *names[i][ft_strchr(*names[i], '.') - 1 - *names[i]];
		if(!ft_isdigit(tmp))
			print_err("bad file name");
		rot = MAX(tmp, rot);
	}
	if (k % rot)
		print_err("missing animation files");
	e->monster[e->curr_m].anim[t] = k;
	e->monster[e->curr_m].a_rot[t] = rot;
}

static void		fetch_f(char ***names, struct dirent *data, int k)
{
	int 		i;

	i = -1;
	if (!bmp_check(data) || k > 49)
		return ;
	if (ft_strlen(data->d_name) > 10)
		print_err("animation file name is too long");
	if (!(*names[k] = (char*)malloc(sizeof(char) * 11)))
		print_err("malloc failed");
	while (++i < 10)
		*names[k][i] = i < ft_strlen(data->d_name) ? data->d_name[i] : '\0';
	*names[k][i] = '\0';
}

void			load_names(t_ed *e, char *p, char ***names, int i)
{
	DIR				*dir;
	struct dirent	*data;
	int 			k;

	dir = NULL;
	k = -1;
	reopen(&dir, p);
	if (!(*names = (char**)malloc(sizeof(char*) * 50)))
		print_err("malloc failed");
	while ((data = readdir(dir)) && (++k + 3))
		fetch_f(names, data, k);
	closedir(dir);
	get_rot(e, k, names, i);
}
