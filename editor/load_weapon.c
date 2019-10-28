/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:55:53 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/26 17:55:55 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		load_wp_tex(t_ed *e, const int n_tex[3], const int n_p[3])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < n_tex[i])
			read_bmp(&e->wp_tex[i][j], e->weapon[i][0][j]);
		j = -1;
		while (++j < n_p[i])
			read_bmp(&e->wp_p[i][j], e->weapon[i][1][j]);
	}
}

void		save_wp_tex(t_ed *e, int n_tex[3], int n_p[3])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 3 && (j = -1))
	{
		while (++j < n_tex[i])
			if (write(e->fd, &e->wp_tex[i][j]->w, sizeof(int)) < 0
			|| write(e->fd, &e->wp_tex[i][j]->h, sizeof(int)) < 0
			|| write(e->fd, e->wp_tex[i][j]->pixels, e->wp_tex[i][j]->h * 4 *
			e->wp_tex[i][j]->w) < 0)
				print_err("saving weapon texture failed");
		j = -1;
		while (++j < n_p[i])
			if (write(e->fd, &e->wp_p[i][j]->w, sizeof(int)) < 0
				|| write(e->fd, &e->wp_p[i][j]->h, sizeof(int)) < 0
				|| write(e->fd, e->wp_p[i][j]->pixels, e->wp_p[i][j]->h * 4 *
				e->wp_p[i][j]->w) < 0)
				print_err("saving weapon projectile texture failed");
	}
}
