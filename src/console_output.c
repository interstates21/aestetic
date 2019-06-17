#include "alt.h"

void print_err(const char *err)
{
    ft_putendl("Something bad happened =( ");
    ft_putendl(err);
    exit(1);
}

void    print_map(t_scene *scene)
{
    ft_putstr("map_height: ");
    ft_putnbr(scene->map_height);
    ft_putchar('\n');
    ft_putstr("map_width: ");
    ft_putnbr(scene->map_width);
    ft_putchar('\n');
    for (int i = 0; i < scene->map_height; i++)
    {
        for(int j = 0; j < scene->map_width; j++)
            ft_putchar(scene->map[i][j]);
        ft_putchar('\n');
    }
}
