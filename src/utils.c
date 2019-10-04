#include "../includes/doom_nukem.h"

double	lerp(double norm, double min, double max)
{
	return (min * (1 - norm) + max * norm);
}

double	norm(double val, double min, double max)
{
	return ((val - min) / (max - min));
}

int		clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double	fclamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int		ft_mod(int i, int n)
{
	return ((i % n + n) % n);
}
