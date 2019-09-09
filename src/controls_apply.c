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

static void player_movement(t_player *player, t_controller *controller, t_scene *scene)
{
    t_v2f temp_dir;

    if (controller->move_forw)
    {
        temp_dir.x += player->anglecos * 0.2f;
        temp_dir.y += player->anglesin * 0.2f;
    }
    if (controller->move_back)
    {
        temp_dir.x -= player->anglecos * 0.2f;
        temp_dir.y -= player->anglesin * 0.2f;
    }
    // if (controller->move_left)
    // {
    //     temp_dir.x += player->anglesin * 0.2f;
    //     temp_dir.y -= player->anglecos * 0.2f;
    // }
    // if (controller->move_right)
    // {
    //     temp_dir.x -= player->anglesin * 0.2f;
    //     temp_dir.y += player->anglecos * 0.2f;
    // }

    player->dir.x = player->dir.x + temp_dir.x;
    player->dir.y = player->dir.y + temp_dir.y;
}

static void player_rotation(t_player *player, t_controller *controller)
{
    t_v2f temp_dir;

    if (controller->move_left)
    {
        temp_dir.x += player->anglesin * 0.2f;
        temp_dir.y -= player->anglecos * 0.2f;
    }
    if (controller->move_right)
    {
        temp_dir.x -= player->anglesin * 0.2f;
        temp_dir.y += player->anglecos * 0.2f;
    }
}

void controls_manager(t_scene *scene)
{

    player_movement(&(scene->player), &(scene->controller), scene);
    player_rotation(&(scene->player), &(scene->controller));

    SDL_Delay(10); 
}