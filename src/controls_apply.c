#include "alt.h"


static void portal_move(t_player *player, const t_sector *current, float dx, float dy)
{
    float px = player->pos.x;
    float py = player->pos.y;
    for(unsigned s = 0; s < current->npoints; ++s)
        if(current->portals[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, current->walls[s+0].x, current->walls[s+0].y, current->walls[s+1].x, current->walls[s+1].y)
        && PointSide(px+dx, py+dy, current->walls[s+0].x, current->walls[s+0].y, current->walls[s+1].x, current->walls[s+1].y) < 0)
        {
            player->sector = current->portals[s];
            break;
        }

    player->pos.x += dx;
    player->pos.y += dy;
    player->anglesin = sinf(player->angle);
    player->anglecos = cosf(player->angle);
}


static void fall(t_player *player, const t_sector *current, t_controller *controller,  float eyeheight) {
            player->dir.z -= 0.05f; /* Add gravity */
            float nextz = player->pos.z + player->dir.z;
            if(player->dir.z < 0 && nextz  < current->floor + eyeheight) // When going down
            {
                /* Fix tocontroller.ground*/
                player->pos.z    = current->floor + eyeheight;
                player->dir.z = 0;
                controller->falling = 0;
                controller->ground = 1;
            }
            else if(player->dir.z > 0 && nextz > current->ceil) // When going up
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

static void move(t_player *player, const t_sector *sectors, const t_sector *current, t_controller *controller, float eyeheight) {
    float px = player->pos.x;
    float py = player->pos.y;
    float dx = player->dir.x;
    float dy = player->dir.y;

            for(unsigned s = 0; s < current->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, current->walls[s+0].x, current->walls[s+0].y, current->walls[s+1].x, current->walls[s+1].y)
                && PointSide(px+dx, py+dy, current->walls[s+0].x, current->walls[s+0].y, current->walls[s+1].x, current->walls[s+1].y) < 0)
                {
                    /* Check pos the hole is. */
                    float hole_low  = current->portals[s] < 0 ?  INFIN : max(current->floor, sectors[current->portals[s]].floor);

                    ft_putnbr(hole_low);
                    ft_putendl("yo !");
                    float hole_high = current->portals[s] < 0 ? -INFIN : min(current->ceil,  sectors[current->portals[s]].ceil );
                    if(hole_high < player->pos.z + HEAD_MARGIN || hole_low  > player->pos.z - eyeheight + KNEE_HEIGHT)
                    {
                        float xd = current->walls[s+1].x - current->walls[s+0].x, yd = current->walls[s+1].y - current->walls[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        controller->moving = 0;
                    }
                }
            portal_move(player, current, dx, dy);
            controller->falling = 1;
}


static void apply_all(t_player *player, const t_controller *controller) {
    t_vt vec = new_v2f(0, 0);

    /* TODO: refactor with rotate_z() */
        if(controller->move_forw) {
            vec.x += player->anglecos * 0.2f;
            vec.y += player->anglesin * 0.2f;
        }
        if(controller->move_back) {
            vec.x -= player->anglecos * 0.2f;
            vec.y -= player->anglesin * 0.2f;
        }
        if(controller->rot_left) {
            vec.x += player->anglesin * 0.2f;
            vec.y -= player->anglecos * 0.2f;
        }
        if(controller->rot_right) {
            vec.x -= player->anglesin * 0.2f;
            vec.y += player->anglecos * 0.2f;
        }
            
        float acceleration = controller->moving ? 0.4 : 0.2;

        player->dir.x = player->dir.x * (1-acceleration) + vec.x * acceleration;
        player->dir.y = player->dir.y * (1-acceleration) + vec.y * acceleration;
}

void controls_manager(t_scene *scene) {

    float eyeheight;
    t_sector *sectors = scene->sectors;
    t_player *player = &(scene->player);
    t_controller *controller = &(scene->controller);


    controller->moving  = controller->move_forw || controller->move_back || controller->rot_left || controller->rot_right;

    eyeheight = controller->ducking ? DEFAULT_DUCK_HEIGHT : DEFAULT_EYE_HEIGHT;
    controller->ground= !controller->falling;

    t_sector * current = &sectors[player->sector];
    if (controller->falling)
        fall(player, current, controller, eyeheight);

    if (controller->moving)
        move(player, sectors, current, controller, eyeheight);
    portal_move(player, current, 0,0);
    apply_all(player, controller);
    // print_v3f(player->pos, "pos");
    
    SDL_Delay(10);
}