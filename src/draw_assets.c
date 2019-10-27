/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:26:21 by bdeomin           #+#    #+#             */
/*   Updated: 2019/10/27 04:22:17 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void	set_assets_value(t_projdata *p, t_vec3f vect, t_three_val container)
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

void	proj_asset(t_data *d, t_projdata *p, t_vec3f vect, SDL_Surface *tex)
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
	set_assets_value(p, vect, container);
}

void	blit_asset(t_data *d, t_projdata *p, SDL_Surface *tex)
{
	t_three_val	container;
	uint32_t	px;

	if ((p->shadefactor = shade_factor(d, p->sector, p->z, 1)) <= 0)
		return ;
	container.one = MAX(p->x1, 0) - 1;
	while (++container.one <= p->x2 && container.one < WIDTH)
	{
		container.two = MAX(p->ya, 0) - 1;
		container.three = NORMALIZE(container.one, p->x1, p->x2) * tex->w;
		while (++container.two < p->yb && container.two < HEIGHT)
		{
			if (p->z < d->zbuffer[container.one + container.two * WIDTH])
			{
				px = pixel_pls(tex, container.three,
								NORMALIZE(container.two, p->ya, p->yb), 3);
				if ((px >> 24) > 127)
					pixel_put(d, new_v3(container.one, container.two, p->z),
										shade(p->shadefactor, px), 1);
			}
		}
	}
}

void	drawing_assets(t_data *d, t_projdata *p, int16_t sectnum, int i)
{
	t_assets	*asset;
	t_vec3f		vect;

	asset = &d->assets[sectnum][i];
	if (!asset->used)
	{
		vect = v2_to_v3(asset->world_pos);
		vect.y = (asset->is_on_floor) ?
			get_floordh(d, p->sector, v3_to_v2(vect)) :
			get_ceildh(d, p->sector, v3_to_v2(vect));
		p->is_on_floor = asset->is_on_floor;
		proj_asset(d, p, vect, d->assets_texture[asset->picnum]);
		blit_asset(d, p, d->assets_texture[asset->picnum]);
	}
}

void	draw_assets(t_data *d, t_projdata *p, int16_t sectnum)
{
	int			i;

	sectnum = p->sector - d->sectors;
	i = -1;
	while (d->nb_assets && ++i < d->assets[sectnum][0].nb_assets)
		drawing_assets(d, p, sectnum, i);
}
