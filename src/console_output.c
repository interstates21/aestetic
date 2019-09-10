#include "alt.h"

void print_err(const char *err)
{
    ft_putendl("Something bad happened =( ");
    ft_putendl(err);
    exit(1);
}

void print_map(t_scene *scene)
{
    ft_putstr("map_height: ");
    ft_putnbr(scene->map_height);
    ft_putchar('\n');
    ft_putstr("map_width: ");
    ft_putnbr(scene->map_width);
    ft_putchar('\n');
    for (int i = 0; i < scene->map_height; i++)
    {
        for (int j = 0; j < scene->map_width; j++)
            ft_putchar(scene->map[i][j]);
        ft_putchar('\n');
    }
}

void print_v2(t_v2i v, char *s)
{
    ft_putstr(s);
    ft_putstr(" = ");
    ft_putnbr(v.x);
    ft_putstr(" -- ");
    ft_putnbr(v.y);
    ft_putchar('\n');
}

void print_v2f(t_vt v, char *s)
{
    ft_putstr(s);
    ft_putstr(" = ");
    ft_putnbr(v.x);
    ft_putstr(" -- ");
    ft_putnbr(v.y);
    ft_putchar('\n');
}

// void     print_v2f(t_vt v, char *s) {
//     printf("Vector %s = x:%f - y:%f", s, v.x, v.y);
// }

void console_log_map(t_scene scene)
{
    int r = -1;
    while (++r < scene.n_sectors)
    {
        int y = -1;
        printf("sector %d:\n\tfloor = %f, ceil = %f\nvertices:\n", r, scene.sectors[r].ceil, scene.sectors[r].floor);
        printf("npoints %d:\n", scene.sectors[r].npoints);
        while (++y < scene.sectors[r].npoints)
            printf("\t(%f, %f)\n", scene.sectors[r].walls[y].x, scene.sectors[r].walls[y].y);
    }
    printf("player:\n\t(%f, %f)\tang = %f\tsect = %d\n", scene.player.pos.x, scene.player.pos.y, scene.player.angle, scene.player.sector);
}