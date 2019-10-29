/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_asseting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:43:58 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/29 21:13:19 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	new_assets_p(t_proj_env *p, t_vec3f vect, t_three_val container)
{
	p->x1 = vect.x - container.one / 2;
	p->x2 = p->x1 + container.one;
	if (!p->is_on_floor)
	{
		p->ya = vect.y;
		p->yb = vect.y + container.two;
	}
	else
	{
		p->ya = vect.y - container.two;
		p->yb = vect.y;
	}
	p->z = vect.z;
}

void	proj_to_asset(t_env *d, t_proj_env *p, t_vec3f vect, SDL_Surface *tex)
{
	double		scale;
	t_three_val	container;

	vect.x -= d->cam.pos.x;
	vect.z -= d->cam.pos.z;
	vect = new_v3(vect.x * d->cam.cos - vect.z * d->cam.sin, vect.y,
		vect.x * d->cam.sin + vect.z * d->cam.cos);
	scale = (1.0 / vect.z) * WIDTH;
	vect.x = vect.x * scale + WIDTH / 2;
	vect.y = vect.y * -scale + HEIGHT / 2 - d->cam.y_offset;
	container.one = scale * tex->w * 0.01;
	container.two = scale * tex->h * 0.01;
	new_assets_p(p, vect, container);
}

void	to_liet_assets(t_env *d, t_proj_env *p, SDL_Surface *tex)
{
	t_three_val	container;
	uint32_t	px;

	if ((p->shadefactor = shd_fct(d, p->sector, p->z, 1)) <= 0)
		return ;
	container.one = MAX(p->x1, 0) - 1;
	while (++container.one <= p->x2 && container.one < WIDTH)
	{
		container.two = MAX(p->ya, 0) - 1;
		container.three = NORMALIZE(container.one, p->x1, p->x2) * tex->w;
		while (++container.two < p->yb && container.two < HEIGHT)
		{
			if (p->z < d->z_buff[container.one + container.two * WIDTH])
			{
				px = pixel_pls(tex, container.three,
								NORMALIZE(container.two, p->ya, p->yb), 3);
				if ((px >> 24) > 127)
					pixel_put(d, new_v3(container.one, container.two, p->z),
										shad(p->shadefactor, px), 1);
			}
		}
	}
}
