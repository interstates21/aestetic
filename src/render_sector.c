#include "../includes/doom_nukem.h"

t_vec3f	transform_back(t_data *d, t_vec3f v)
{
	return (new_v3(v.x * d->cam.cos + v.z * d->cam.sin + d->cam.pos.x, v.y,
			v.x * -d->cam.sin + v.z * d->cam.cos + d->cam.pos.z));
}

void		transformvertex(t_data *d, t_vec2f v, double *x, double *z)
{
	v.x -= d->cam.pos.x;
	v.y -= d->cam.pos.z;
	*x = v.x * d->cam.cos - v.y * d->cam.sin;
	*z = v.x * d->cam.sin + v.y * d->cam.cos;
}

t_sector	*check_neighbor(t_data *d, int16_t nei)
{
	if (nei < 0 || nei >= d->numsectors)
		return (NULL);
	return (&d->sectors[nei]);
}

void		render_wall(t_data *d, t_projdata *p, t_frustum *fr, int i)
{
	p->wall = &d->walls[p->sector->firstwallnum + i];
	p->wall2 = &d->walls[p->sector->firstwallnum +
		(i + 1) % p->sector->numwalls];
	transformvertex(d, p->wall->point, &p->x1, &p->z1);
	transformvertex(d, p->wall2->point, &p->x2, &p->z2);
	p->neighbor = check_neighbor(d, p->wall->neighborsect);
	p->wall->lowerpicnum = p->wall2->middlepicnum;
	p->len = v2_len(new_v2(p->x2 - p->x1, p->z2 - p->z1));
	p->u1 = 0;
	p->u2 = p->len;
	if ((p->z1 <= 0 && p->z2 <= 0) || ((p->z1 <= 0) &&
			!(clip_wall(&p->x1, &p->z1, p->x2, p->z2) && (p->u1 = p->u2 -
			v2_len(new_v2(p->x2 - p->x1, p->z2 - p->z1))))) ||
			((p->z2 <= 0) && !(clip_wall(&p->x2, &p->z2, p->x1, p->z1) &&
			(p->u2 = v2_len(new_v2(p->x2 - p->x1, p->z2 - p->z1))))))
		return ;
	proj_wall(d, p, fr, (t_vec2f[2]){
			v3_to_v2(transform_back(d, new_v3(p->x1, 0, p->z1))),
			v3_to_v2(transform_back(d, new_v3(p->x2, 0, p->z2)))});
}

void	proj_ceil_or_floor(t_data *d, t_projdata *p, int mode)
{
	mode == 0 ? (p->b[0] = transform_back(d, new_v3(-1, 0, 1))) :
				(p->c[0] = transform_back(d, new_v3(-1, 0, 1)));
	mode == 0 ? (p->b[1] = transform_back(d, new_v3(1, 0, 1))) :
				(p->c[1] = transform_back(d, new_v3(1, 0, 1)));
	mode == 0 ? (p->b[2] = transform_back(d, new_v3z(2))) :
				(p->c[2] = transform_back(d, new_v3z(2)));
	mode == 0 ? (p->a[0] = new_v3(-WIDTH + WIDTH / 2, get_ceildh(d,
		p->sector, v3_to_v2(p->b[0])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset),
		1)) : (p->v[0] = new_v3(-WIDTH + WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[0])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset), 1));
	mode == 0 ? (p->a[1] = new_v3(WIDTH + WIDTH / 2, get_ceildh(d,
		p->sector, v3_to_v2(p->b[1])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset),
		1)) : (p->v[1] = new_v3(WIDTH + WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[1])) * -WIDTH + (HEIGHT / 2 - d->cam.y_offset), 1));
	mode == 0 ? (p->a[2] = new_v3(WIDTH / 2, get_ceildh(d, p->sector,
		v3_to_v2(p->b[2])) * -WIDTH * 0.5 + (HEIGHT / 2 - d->cam.y_offset),
		0.5)) : (p->v[2] = new_v3(WIDTH / 2, get_floordh(d, p->sector,
		v3_to_v2(p->c[2])) * -WIDTH * 0.5 + (HEIGHT / 2 - d->cam.y_offset),
		0.5));
	mode == 0 ? (p->b[2].x /= 2) : (p->c[2].x /= 2);
	mode == 0 ? (p->b[2].z /= 2) : (p->c[2].z /= 2);
	mode == 0 ? (p->areaa = edge_function(p->a[0], p->a[1],
												p->a[2].x, p->a[2].y)) :
		(p->area = edge_function(p->v[0], p->v[1], p->v[2].x, p->v[2].y));
}

void		render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	t_sprite_list	*sprite_list_tmp;
	t_projdata		p;
	int				i;

	p.sector = sect;
	proj_ceil_or_floor(d, &p, 0);
	proj_ceil_or_floor(d, &p, 1);
	i = -1;
	while (++i < WIDTH)
		p.zbuffer[i] = INFINITY;
	i = -1;
	while (++i < sect->numwalls)
		render_wall(d, &p, fr, i);
	if (sect->sprite_list)
		reorder_sprite(d, sect);
	sprite_list_tmp = sect->sprite_list;
	while (sprite_list_tmp)
	{
		draw_sprite(d, fr, sprite_list_tmp);
		sprite_list_tmp = sprite_list_tmp->next;
	}
	d_asseting(d, &p, sect - d->sectors);
}
