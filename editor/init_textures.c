/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:25:15 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/17 16:25:16 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static void			count_tex(DIR **dir, int *i)
{
	struct dirent	*data;

	reopen(dir, TEXT_DIR);
	*i = 0;
	while ((data = readdir(*dir)))
	{
		if (bmp_check(data))
			*i += 1;
	}
	if (*i == 0)
		print_err("no textures found");
}

static void			init_tex(char *name, t_texlist *tex, int i)
{
	char			*tmp;

	tmp = ft_strjoin(TEXT_DIR, name);
	tex->n_tex = i;
	ft_strcpy(tex->name, tmp);
	free(tmp);
	tex->tex = NULL;
}

static void			get_tex_names(t_ed *e, DIR **dir)
{
	struct dirent	*data;
	int				i;

	reopen(dir, TEXT_DIR);
	i = 0;
	while ((data = readdir(*dir)))
		if (bmp_check(data))
		{
			init_tex(data->d_name, &e->texlist[i], i);
			i++;
		}
}

void				init_textures(t_ed *e)
{
	DIR				*dir;
	int				i;

	dir = NULL;
	count_tex(&dir, &e->n_tex);
	e->texlist = (t_texlist*)malloc(sizeof(t_texlist) * e->n_tex);
	get_tex_names(e, &dir);
	closedir(dir);
	i = -1;
	while (++i < e->n_tex)
		read_bmp(&e->texlist[i].tex, e->texlist[i].name);
}
