#include "../includes/editor.h"

int		trim(int v, int inc)
{
	while (v % GRID_GAP)
		v += inc;
	return (v);
}

void	print_err(const char *err)
{
	ft_putstr("Init Error = ");
	ft_putendl(err);
	exit(1);
}
