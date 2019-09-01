/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdeomin <bdeomin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 18:24:17 by bdeomin           #+#    #+#             */
/*   Updated: 2019/08/23 18:24:22 by bdeomin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alt.h"
#define INFIN 9e9
// void        complex_movement() {

//  float eyeheight =controller->ducking ? DuckHeight : EyeHeight;
//        controller->ground= !controller->falling;
//         if(controller->falling)
//         {
//             player->dir.z -= 0.05f; /* Add gravity */
//             float nextz = player->pos.z + player->dir.z;
//             if(player->dir.z < 0 && nextz  < sectors[player->sector].floor + eyeheight) // When going down
//             {
//                 /* Fix tocontroller.ground*/
//                 player->pos.z    = sectors[player->sector].floor + eyeheight;
//                 player->dir.z = 0;
//                 controller->falling = 0;
//                controller->ground = 1;
//             }
//             else if(player->dir.z > 0 && nextz > sectors[player->sector].ceil) // When going up
//             {
//                 /* Prevent jumping above ceiling */
//                 player->dir.z = 0;
//                 controller->falling = 1;
//             }
//             if(controller->falling)
//             {
//                 player->pos.z += player->dir.z;
//                 controller->moving = 1;
//             }
//         }
//         /* Horizontal collision detection */
// }

bool        check_something(t_player *player, t_v2f current_point, t_v2f next_point) {
    return (
        IntersectBox(
        player->pos.x,
        player->pos.y,
        player->pos.x + player->dir.x,
        player->pos.y + player->dir.y,
        current_point.x,
        current_point.y,
        next_point.x,
        next_point.y)
        &&
        PointSide(
        player->pos.x + player->dir.x,
        player->pos.y + player->dir.y,
        current_point.x,
        current_point.y, 
        next_point.x,
        next_point.y) < 0);
}



static void apply_movement(t_player *player, t_sector current_sector, t_v2f *vertices)
{
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    int n;
    n = 0;

    while ( n < current_sector.npoints) {
        if (check_something(player, vertices[n], vertices[n + 1]))
            player->sector = current_sector.portals[n];
            // todo save a portal inside a wall
        n++;
    }

    player->pos.x += player->dir.x;
    player->pos.y += player->dir.y; 
    player->anglesin = sin(player->angle);
    player->anglecos = cos(player->angle);
}


// void bump_aside() {
//  /* Bumps into a wall! Slide along the wall. */
//                         /* This formula is from Wikipedia article "vector projection". */
//                         float xd = vert[n+1].x - vert[n].x, yd = vert[n+1].y - vert[n].y;
//                         dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
//                         dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
//                         controller->moving = 0;
// }

// bool wall_collision() {

//     return ((hole_high < player->pos.z+HeadMargin || hole_low  > player->pos.z-eyeheight+KneeHeight))
// }

void move(t_player *player, t_scene *scene)
{
            float deep;
            float hight;
            int   n;
            t_sector  current_sector  = scene->sectors[player->sector];
            t_v2f     *vertices        = current_sector.vertex;

            n = 0;
    
            while ( n < current_sector.npoints) {
            if (check_something(player, current_sector.vertex[n], current_sector.vertex[n + 1])) {
                // deep  = current_sector.portals[n] < 0 ?  INFIN : max(current_sector.floor, sectors[current_sector.portals[n]].floor);
                // hight = current_sector.portals[n] < 0 ? -INFIN : min(current_sector.ceil,  sectors[current_sector.portals[n]].ceil );
            }
                // if (wall_collision())
                //     bump_aside();      
                n++;

            }
            apply_movement(player, current_sector, vertices);
}


static void        player_movement(t_player *player, t_controller *controller, t_scene *scene) {
    t_v2f temp_dir;

    if(controller->move_forw)
        {
            temp_dir.x += player->anglecos * 0.2f;
            temp_dir.y += player->anglesin * 0.2f;
        }
        if(controller->move_back)
        {
            temp_dir.x -= player->anglecos * 0.2f;
            temp_dir.y -= player->anglesin * 0.2f;
        }
        if(controller->move_left)
        {
            temp_dir.x += player->anglesin * 0.2f;
            temp_dir.y -= player->anglecos * 0.2f;
        }
        if(controller->move_right)
        {
            temp_dir.x -= player->anglesin * 0.2f;
            temp_dir.y += player->anglecos * 0.2f;
        }

        float acceleration = true ? 0.4 : 0.2; // why?

        player->dir.x = player->dir.x * (1 - acceleration) + temp_dir.x * acceleration;
        player->dir.y = player->dir.y * (1 - acceleration) + temp_dir.y * acceleration;

        move(player, scene);
        controller->falling = 1; // why?
}


static void player_rotation(t_player *player, t_controller controller) {
    float temp_yaw = clamp(player->yaw - controller.mouse.y * (-0.025f), -5, 5);
    player->angle += controller.mouse.x * 0.007f;
	player->yaw = temp_yaw - player->dir.z * 0.5f;
}


static void player_jump(t_player *player) {
    player->dir.z += 0.5;
    player->falling = 1;
    // if (!player->falling)
	// {
	// 	player->dir.z += 0.5;
	// 	controller->falling = 1;
	// }
}

static void player_squat(t_player *player) {
    player->falling = 1;
}


void controls_manager(t_scene *scene) {

    bool    moving =
            scene->controller.move_forw ||
            scene->controller.move_back ||
            scene->controller.move_left  ||
            scene->controller.move_right ?
            true : false;

    if (moving) {
        player_movement(&(scene->player), &(scene->controller), scene);
    }
    if (scene->controller.rotating) {
        player_rotation(&(scene->player), scene->controller);
    }
    if (scene->controller.jumping) {
        player_jump(&(scene->player));
    }
    if (scene->controller.squat) {
        player_squat(&(scene->player));
    }
    // apply_player_gravity


    SDL_Delay(10); // why
} 