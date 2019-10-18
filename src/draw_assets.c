#include "../includes/doom_nukem.h"

void	set_assets_value(t_projdata *p, t_vec3f v, int w, int h)
{
	p->x1 = v.x - w / 2;
	p->x2 = p->x1 + w;
	if (p->is_on_floor)
	{
		p->ya = v.y - h;
		p->yb = v.y;
	}
	else
	{
		p->ya = v.y;
		p->yb = v.y + h;
	}
	p->z = v.z;
}

void	proj_asset(t_data *d, t_projdata *p, t_vec3f v, SDL_Surface *tex)
{
	double	scale;
	int		width;
	int		height;

	v.x -= d->cam.pos.x;
	v.z -= d->cam.pos.z;
	v = (t_vec3f){v.x * d->cam.cos - v.z * d->cam.sin, v.y,
		v.x * d->cam.sin + v.z * d->cam.cos};
	scale = (1.0 / v.z) * WIDTH;
	v.x = v.x * scale + WIDTH / 2;
	v.y = v.y * -scale + HEIGHT / 2 - d->cam.y_offset;
	width = scale * tex->w * 0.01;
	height = scale * tex->h * 0.01;
	set_assets_value(p, v, width, height);
}

void	blit_asset(t_data *d, t_projdata *p, SDL_Surface *tex)
{
	int			x;
	int			y;
	int			u;
	uint32_t	px;

	if ((p->shadefactor = getshadefactor(d, p, p->z)) <= 0)
		return ;
	x = MAX(p->x1, 0) - 1;
	while (++x <= p->x2 && x < WIDTH)
	{
		u = NORMALIZE(x, p->x1, p->x2) * tex->w;
		y = MAX(p->ya, 0) - 1;
		while (++y < p->yb && y < HEIGHT)
		{
			if (p->z >= d->zbuffer[x + y * WIDTH])
				continue ;
			px = getpixel4(tex, u, NORMALIZE(y, p->ya, p->yb));
			if ((px >> 24) > 127)
				putpixel2(d, p->z, (t_vec2){x, y}, shade(p->shadefactor, px));
		}
	}
}

void	draw_assets(t_data *d, t_projdata *p, int16_t sectnum)
{
	int			i;
	t_assets	*asset;
	t_vec3f		v;

	sectnum = p->sector - d->sectors;
	i = -1;
	while (d->nb_assets && ++i < d->assets[sectnum][0].nb_assets)
	{
		asset = &d->assets[sectnum][i];
		if (asset->used)
			continue ;
		v = v2_to_v3(asset->world_pos);
		v.y = (asset->is_on_floor) ? get_floordh(d, p->sector, v3_to_v2(v)) :
			get_ceildh(d, p->sector, v3_to_v2(v));
		p->is_on_floor = asset->is_on_floor;
		proj_asset(d, p, v, d->assets_texture[asset->picnum]);
		blit_asset(d, p, d->assets_texture[asset->picnum]);
	}
}
