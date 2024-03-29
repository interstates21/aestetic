#include "../includes/doom_nukem.h"

double	*get_screen_pixels(void)
{
	double	*arr;
	size_t	memory_size;

	memory_size = sizeof(double) * WIDTH * HEIGHT;
	arr = (double*)pure_malloc(memory_size, "pixels allocation failed");
	return (arr);
}

void	*pure_malloc(size_t size, const char *err)
{
	void	*data;

	data = malloc(size);
	if (!data)
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(1);
	}
	return (data);
}
