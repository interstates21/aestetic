#include "../includes/doom_nukem.h"


double	get_floorheight_player(t_data *d, int16_t sectnum)
{
	double floorHeight;
	floorHeight = getFloorHeight(&d->sectors[sectnum], d->walls, sectnum, v3_to_v2(d->cam.pos));
	return (floorHeight);
}

double	get_ceilheight_player(t_data *d, int16_t sectnum)
{
	double ceilHeight;		
	ceilHeight = getCeilHeight(&d->sectors[sectnum], d->walls, sectnum, v3_to_v2(d->cam.pos));		
	return (ceilHeight);
}


double	get_floordh(t_data *d, t_sector *sect, t_vec2f v)
{
	double floorHeight;
	floorHeight = getFloorHeight(&d->sectors[sect - d->sectors], d->walls, sect - d->sectors, v);
	return (floorHeight - d->cam.pos.y);
}

double	get_ceildh(t_data *d, t_sector *sect, t_vec2f v)
{
	double ceilHeight;
	ceilHeight = getCeilHeight(&d->sectors[sect - d->sectors], d->walls, sect - d->sectors, v);
	return (ceilHeight - d->cam.pos.y);
}
