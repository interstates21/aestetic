#include "../includes/doom_nukem.h"

double	lerp(double norm, double min, double max)
{
	return (min * (1 - norm) + max * norm);
}

double	norm(double val, double min, double max)
{
	return ((val - min) / (max - min));
}

int		ft_mod(int i, int n)
{
	return ((i % n + n) % n);
}
