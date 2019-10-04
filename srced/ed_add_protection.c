#include "editor.h"

/*
**	Protection for max walls and sectors
*/

void		add_wall_protection(t_data *d)
{
	if (d->numwalls < MAXNUMWALLS)
		add_wall(d);
	else
		printf("Too much walls already.\n");
}

void		add_sector_protection(t_data *d)
{
	if (d->numsectors < MAXNUMSECTORS)
		add_sector(d);
	else
		printf("Too much sectors already.\n");
}
