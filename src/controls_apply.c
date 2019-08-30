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
#define EPSILON 2 // FIXING SMASHING INTO TEXTURES

static void	apply_rot_left(t_player *player)
{
	rotate_z(&(player->view), player->rot_speed);
	rotate_z(&(player->dir), player->rot_speed);
}

static void	apply_rot_right(t_player *player)
{
	rotate_z(&(player->view), -player->rot_speed);
	rotate_z(&(player->dir), -player->rot_speed);
}

static void	apply_move_forvard(t_player *player, char **map)
{
	double	new_pos_x;
	double	new_pos_y;
	double	pos_x;
	double	pos_y;

	pos_x = player->pos.x;
	pos_y = player->pos.y;

    new_pos_x = pos_x + player->dir.x * EPSILON * player->move_speed;
    new_pos_y = pos_y + player->dir.y * EPSILON * player->move_speed;
    ///
	new_pos_x = pos_x + player->dir.x * EPSILON * player->move_speed;
	new_pos_y = pos_y + player->dir.y * EPSILON * player->move_speed;
	if (map[(int)pos_x][(int)new_pos_y] == '0')
		player->pos.y = new_pos_y;
	if (map[(int)new_pos_x][(int)pos_y] == '0')
		player->pos.x = new_pos_x;
}

static void	apply_move_back(t_player *player, char **map)
{
	double	new_pos_x;
	double	new_pos_y;
	double	pos_x;
	double	pos_y;

	pos_x = player->pos.x;
	pos_y = player->pos.y;

	new_pos_x = pos_x - player->dir.x * player->move_speed;
	new_pos_y = pos_y - player->dir.y * player->move_speed;
	if (map[(int)pos_x][(int)new_pos_y] == '0')
		player->pos.y = new_pos_y;
	if (map[(int)new_pos_x][(int)pos_y] == '0')
		player->pos.x = new_pos_x;
}

   // new_pos_x = pos_x - player->dir.x * player->move_speed;
   // new_pos_y = pos_y - player->dir.y * player->move_speed;
    ///
void	apply_mouse_rot(t_player *player, int x, int y)
{
	printf("x = %d; y = %d;\n", x, y);
}

void		apply_controls(t_player *player, char **map)
{
	if (player->move_forw)
		apply_move_forvard(player, map);
	if (player->move_back)
		apply_move_back(player, map);
	if (player->rot_left)
		apply_rot_left(player);
	if (player->rot_right)
		apply_rot_right(player);
}

void		test_controls(t_player *player, char **map)
{
	(void)map;
	if (player->move_forw)
		player->pos.y += 1;
	if (player->move_back)
		player->pos.y -= 1;
	if (player->rot_left)
		player->pos.x += 1;
	if (player->rot_right)
		player->pos.x -= 1;
}
