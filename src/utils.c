#include "../includes/doom_nukem.h"

double	lerp(double norm, double min, double max)
{
	return (min * (1 - norm) + max * norm);
}
