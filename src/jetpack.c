#include "../includes/doom_nukem.h"

void	decrease_fuel(t_data *d)
{
	d->player.is_flying -= 1;
	if (!d->player.is_flying)
	{
		if (d->slot2 && d->slot2->is_jetpack)
			d->slot2 = NULL;
		if (d->slot3 && d->slot3->is_jetpack)
			d->slot3 = NULL;
	}
}
