#include "../includes/doom_nukem.h"

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
	p->len = v2_len((t_vec2f){p->x2 - p->x1, p->z2 - p->z1});
	p->u1 = 0;
	p->u2 = p->len;
	if ((p->z1 <= 0 && p->z2 <= 0) || ((p->z1 <= 0) &&
			!(clip_wall(&p->x1, &p->z1, p->x2, p->z2) && (p->u1 = p->u2 -
			v2_len((t_vec2f){p->x2 - p->x1, p->z2 - p->z1})))) ||
			((p->z2 <= 0) && !(clip_wall(&p->x2, &p->z2, p->x1, p->z1) &&
			(p->u2 = v2_len((t_vec2f){p->x2 - p->x1, p->z2 - p->z1})))))
		return ;
	proj_wall(d, p, fr, (t_vec2f[2]){
			v3_to_v2(transform_back(d, (t_vec3f){p->x1, 0, p->z1})),
			v3_to_v2(transform_back(d, (t_vec3f){p->x2, 0, p->z2}))});
}

void		render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	t_sprite_list	*sprite_list_tmp;
	t_projdata		p;
	int				i;

	p.sector = sect;
	proj_floor(d, &p);
	proj_ceil(d, &p);
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
	draw_assets(d, &p, sect - d->sectors);
}
