/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:59:00 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/26 16:59:01 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void			write_tex_list(t_ed *e)
{
	uint32_t	tmp;
	int			i;

	tmp = e->n_used_tex;
	if (write(e->fd, &tmp, sizeof(int32_t)) < 0)
		print_err("saving n_tex failed");
	i = -1;
	while (++i < e->n_tex)
		if (e->used_tex[i])
			if (write(e->fd, e->texlist[i].name, MAX_NAME) < 0)
				print_err("saving texture name failed");
}

void			write_tex_data(t_ed *e)
{
	int			i;
	int			v[2];

	i = -1;
	while (++i < e->n_tex)
		if (e->used_tex[i])
		{
			v[0] = e->texlist[i].tex->w;
			v[1] = e->texlist[i].tex->h;
			if (write(e->fd, &v[0], sizeof(int)) < 0
			|| write(e->fd, &v[1], sizeof(int)) < 0
			|| write(e->fd, e->texlist[i].tex->pixels, 4 * (v[0] * v[1])) < 0)
				print_err("saving texture failed");
		}
}

void			write_posters(t_ed *e)
{
	int32_t		n;

	n = 0;
	if (write(e->fd, &n, sizeof(int32_t)) < 0)
		print_err("saving n_posters failed");
}
