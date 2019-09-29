#include "alt.h"



void	apply_mouse_controls(t_player *player, t_controller *controller)
{
	SDL_GetRelativeMouseState(&controller->mouse.x, &controller->mouse.y);
	if (SDL_GetRelativeMouseMode())
	{
		player->angle += controller->mouse.x * 0.007f;
		controller->yaw = clamp(controller->yaw - controller->mouse.y * (-0.025f), -5, 5);
		player->yaw = controller->yaw - player->dir.z * 0.5f;
	}
}

static void MovePlayer(t_scene *scene, float dx, float dy)
{
    float px = scene->player.pos.x;
    float py = scene->player.pos.y;
    /* Check if this movemewnt crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    t_sector*  sect = &(scene->sectors[scene->player.sector]);
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->portals[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, sect->walls[s+0].x, sect->walls[s+0].y, sect->walls[s+1].x, sect->walls[s+1].y)
        && PointSide(px+dx, py+dy, sect->walls[s+0].x, sect->walls[s+0].y, sect->walls[s+1].x, sect->walls[s+1].y) < 0)
        {
            scene->player.sector = sect->portals[s];
            break;
        }

    scene->player.pos.x += dx;
    scene->player.pos.y += dy;
    scene->player.anglesin = sinf(scene->player.angle);
    scene->player.anglecos = cosf(scene->player.angle);
}

// void controls_manager( ) {

// }

void aplly_controls(t_scene *scene, bool *end, t_sdl sdl) {

    t_sector *sectors = scene->sectors;
    t_player *player = &(scene->player);
    t_controller *controller = &(scene->controller);

 float eyeheight =controller->ducking ? DuckHeight : EyeHeight;
       controller->ground= !controller->falling;
        if(controller->falling)
        {
            player->dir.z -= 0.05f; /* Add gravity */
            float nextz = player->pos.z + player->dir.z;
            if(player->dir.z < 0 && nextz  < sectors[player->sector].floor + eyeheight) // When going down
            {
                /* Fix tocontroller.ground*/
                player->pos.z    = sectors[player->sector].floor + eyeheight;
                player->dir.z = 0;
                controller->falling = 0;
               controller->ground = 1;
            }
            else if(player->dir.z > 0 && nextz > sectors[player->sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                player->dir.z = 0;
                controller->falling = 1;
            }
            if(controller->falling)
            {
                player->pos.z += player->dir.z;
                controller->moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(controller->moving)
        {
            float px = player->pos.x,    py = player->pos.y;
            float dx = player->dir.x, dy = player->dir.y;

            t_sector * sect = &sectors[player->sector];
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, sect->walls[s+0].x, sect->walls[s+0].y, sect->walls[s+1].x, sect->walls[s+1].y)
                && PointSide(px+dx, py+dy, sect->walls[s+0].x, sect->walls[s+0].y, sect->walls[s+1].x, sect->walls[s+1].y) < 0)
                {
                    /* Check pos the hole is. */
                    float hole_low  = sect->portals[s] < 0 ?  9e9 : max(sect->floor, sectors[sect->portals[s]].floor);
                    float hole_high = sect->portals[s] < 0 ? -9e9 : min(sect->ceil,  sectors[sect->portals[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < player->pos.z+HeadMargin
                    || hole_low  > player->pos.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = sect->walls[s+1].x - sect->walls[s+0].x, yd = sect->walls[s+1].y - sect->walls[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        controller->moving = 0;
                    }
                }
            MovePlayer(scene, dx, dy);
            controller->falling = 1;
        }

        MovePlayer(scene, 0,0);

        float move_vec[2] = {0.f, 0.f};
        if(controller->move_forw) { move_vec[0] += player->anglecos*0.2f; move_vec[1] += player->anglesin*0.2f; }
        if(controller->move_back) { move_vec[0] -= player->anglecos*0.2f; move_vec[1] -= player->anglesin*0.2f; }
        if(controller->rot_left) { move_vec[0] += player->anglesin*0.2f; move_vec[1] -= player->anglecos*0.2f; }
        if(controller->rot_right) { move_vec[0] -= player->anglesin*0.2f; move_vec[1] += player->anglecos*0.2f; }
        int pushing = controller->move_forw || controller->move_back || controller->rot_left || controller->rot_right;
        float acceleration = pushing ? 0.4 : 0.2;

        player->dir.x = player->dir.x * (1-acceleration) + move_vec[0] * acceleration;
        player->dir.y = player->dir.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) controller->moving = 1;

        SDL_Delay(10);
}



