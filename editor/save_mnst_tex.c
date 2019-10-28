/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_mnst_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolomoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 19:02:09 by akolomoi          #+#    #+#             */
/*   Updated: 2019/10/26 19:02:12 by akolomoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static int	ani(t_ed *e, SDL_Surface **s, int n_a)
{
	int		i;

	i = -1;
	while (++i < n_a)
		if (write(e->fd, &s[i]->w, sizeof(int)) < 0
		|| write(e->fd, &s[i]->h, sizeof(int)) < 0
		|| write(e->fd, s[i]->pixels, 4 * s[i]->w * s[i]->h) < 0)
			return (1);
	return (0);
}

void		write_sprt_tex(t_ed *e)
{
	int		i;
	int16_t	tmp;

	tmp = e->n_sprites;
	if (write(e->fd, &tmp, sizeof(int16_t)) < 0)
		print_err("saving n_sprites failed");
	i = -1;
	while (++i < e->n_sprites)
		if (write(e->fd, &e->sprites[i].texture->w, sizeof(int)) < 0
		|| write(e->fd, &e->sprites[i].texture->h, sizeof(int)) < 0
		|| write(e->fd, e->sprites[i].texture->pixels, 4 *
		e->sprites[i].texture->w * e->sprites[i].texture->h) < 0)
			print_err("saving sprite textures failed");
}

void		write_mons_tex(t_ed *e)
{
	int		i;

	i = -1;
	while (++i < M_TOTAL)
		if (write(e->fd, &e->monster[i].a_rot[A_WALK], sizeof(int)) < 0
		|| ani(e, e->monster[i].acting[A_WALK], e->monster[i].anim[A_WALK])
		|| ani(e, e->monster[i].acting[A_ATTACK], e->monster[i].anim[A_ATTACK])
		|| write(e->fd, &e->monster[i].anim[A_DIE], sizeof(int)) < 0
		|| ani(e, e->monster[i].acting[A_DIE], e->monster[i].anim[A_DIE]))
			print_err("saving monster textures failed");
	if (ani(e, e->m_projec, 5))
		print_err("saving projectile failed");
}
