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
// #define EPSILON 2 // FIXING SMASHING INTO TEXTURES

// static void	apply_rot_left(t_player *player)
// {
// 	rotate_z(&(player->view), player->rot_speed);
// 	rotate_z(&(player->dir), player->rot_speed);
// }

// static void	apply_rot_right(t_player *player)
// {
// 	rotate_z(&(player->view), -player->rot_speed);
// 	rotate_z(&(player->dir), -player->rot_speed);
// }

// static void	apply_move_forvard(t_player *player, char **map)
// {
// 	double	new_pos_x;
// 	double	new_pos_y;
// 	double	pos_x;
// 	double	pos_y;

// 	pos_x = player->pos.x;
// 	pos_y = player->pos.y;

//     new_pos_x = pos_x + player->dir.x * EPSILON * player->move_speed;
//     new_pos_y = pos_y + player->dir.y * EPSILON * player->move_speed;
//     ///
// 	new_pos_x = pos_x + player->dir.x * EPSILON * player->move_speed;
// 	new_pos_y = pos_y + player->dir.y * EPSILON * player->move_speed;
// 	if (map[(int)pos_x][(int)new_pos_y] == '0')
// 		player->pos.y = new_pos_y;
// 	if (map[(int)new_pos_x][(int)pos_y] == '0')
// 		player->pos.x = new_pos_x;
// }

// static void	apply_move_back(t_player *player, char **map)
// {
// 	double	new_pos_x;
// 	double	new_pos_y;
// 	double	pos_x;
// 	double	pos_y;

// 	pos_x = player->pos.x;
// 	pos_y = player->pos.y;

// 	new_pos_x = pos_x - player->dir.x * player->move_speed;
// 	new_pos_y = pos_y - player->dir.y * player->move_speed;
// 	if (map[(int)pos_x][(int)new_pos_y] == '0')
// 		player->pos.y = new_pos_y;
// 	if (map[(int)new_pos_x][(int)pos_y] == '0')
// 		player->pos.x = new_pos_x;
// }

//    // new_pos_x = pos_x - player->dir.x * player->move_speed;
//    // new_pos_y = pos_y - player->dir.y * player->move_speed;
//     ///
// void	apply_mouse_rot(t_player *player, int x, int y)
// {
// 	printf("x = %d; y = %d;\n", x, y);
// }

// void		apply_controls(t_player *player, char **map)
// {
// 	if (player->move_forw)
// 		apply_move_forvard(player, map);
// 	if (player->move_back)
// 		apply_move_back(player, map);
// 	if (player->rot_left)
// 		apply_rot_left(player);
// 	if (player->rot_right)
// 		apply_rot_right(player);
// }

// void		test_controls(t_player *player, char **map)
// {
// 	(void)map;
// 	if (player->move_forw)
// 		player->pos.y += 1;
// 	if (player->move_back)
// 		player->pos.y -= 1;
// 	if (player->rot_left)
// 		player->pos.x += 1;
// 	if (player->rot_right)
// 		player->pos.x -= 1;
// }


static void MovePlayer(float dx, float dy)
{
    float px = player.where.x, py = player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }

    player.where.x += dx;
    player.where.y += dy;
    player.anglesin = sinf(player.angle);
    player.anglecos = cosf(player.angle);
}

void shitty_controller(t_controller *controller, bool *end, t_sdl sdl) {

 float eyeheight =controller->ducking ? DuckHeight : EyeHeight;
       controller->ground= !controller->falling;
        if(controller->falling)
        {
            player.velocity.z -= 0.05f; /* Add gravity */
            float nextz = player.where.z + player.velocity.z;
            if(player.velocity.z < 0 && nextz  < sectors[player.sector].floor + eyeheight) // When going down
            {
                /* Fix tocontroller.ground*/
                player.where.z    = sectors[player.sector].floor + eyeheight;
                player.velocity.z = 0;
                controller->falling = 0;
               controller->ground = 1;
            }
            else if(player.velocity.z > 0 && nextz > sectors[player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                player.velocity.z = 0;
                controller->falling = 1;
            }
            if(controller->falling)
            {
                player.where.z += player.velocity.z;
                controller->moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(controller->moving)
        {
            float px = player.where.x,    py = player.where.y;
            float dx = player.velocity.x, dy = player.velocity.y;

            const struct sector* const sect = &sectors[player.sector];
            const struct xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, sectors[sect->neighbors[s]].floor);
                    float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < player.where.z+HeadMargin
                    || hole_low  > player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        controller->moving = 0;
                    }
                }
            MovePlayer(dx, dy);
            controller->falling = 1;
        }

        listen_controls(&player, end, controller);
        /* mouse aiming */
        mouse_aiming(&player, controller);
        MovePlayer(0,0);

        float move_vec[2] = {0.f, 0.f};
        if(controller->move_forw) { move_vec[0] += player.anglecos*0.2f; move_vec[1] += player.anglesin*0.2f; }
        if(controller->move_back) { move_vec[0] -= player.anglecos*0.2f; move_vec[1] -= player.anglesin*0.2f; }
        if(controller->rot_left) { move_vec[0] += player.anglesin*0.2f; move_vec[1] -= player.anglecos*0.2f; }
        if(controller->rot_right) { move_vec[0] -= player.anglesin*0.2f; move_vec[1] += player.anglecos*0.2f; }
        int pushing = controller->move_forw || controller->move_back || controller->rot_left || controller->rot_right;
        float acceleration = pushing ? 0.4 : 0.2;

        player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) controller->moving = 1;

        SDL_Delay(10);
}
