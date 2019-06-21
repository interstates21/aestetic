#include "alt.h"

/*
ray:
    t_v2f	dir;
	t_v2	move_side;
	t_v2    cell;
    t_v2f   dist;
    t_v2f   dist_delta;
    char    hit_side;
    bool    is_hit;
    double  dist_hit;
*/

bool       is_wall(char **map, t_v2 pos)
{
    return (map[pos.x] && map[pos.x][pos.y] != '0');
}

void        cast_ray(t_scene *scene, t_ray *ray, int x)
{
    ray->is_hit = false;

    while (!ray->is_hit)
    {
        /*  find absolute and delta dists to either x edge or y edge */
        if (ray->dist.x < ray->dist.y)
        {
            ray->dist.x += ray->dist_delta.x;
            ray->cell.x += ray->move_side.x;
            ray->hit_side = 'e';
        }
        else
        {
            ray->dist.y += ray->dist_delta.y;
            ray->cell.y += ray->move_side.y;
            ray->hit_side = 'w';
        }
        ray->is_hit = is_wall(scene->map, ray->cell);
    }

    /* Either X or Y dist. Y in the world coordinate frame is X in a WallCell frame */
    ray->dist_hit = ray->hit_side == 'e'
    ? (ray->cell.x - scene->player.pos.x + (1 - ray->move_side.x) / 2) / ray->dir.x
    : (ray->cell.y - scene->player.pos.y + (1 - ray->move_side.y) / 2) / ray->dir.y;

    render_line(scene, ray, x );
}
