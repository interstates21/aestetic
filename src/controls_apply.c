#include "alt.h"
#define EPSILON 2 // FIXING SMASHING INTO TEXTURES

static void    apply_rot_left(t_player *player)
{
    rotate_z(&(player->view), player->rot_speed);
	rotate_z(&(player->dir), player->rot_speed);
}

static void    apply_rot_right(t_player *player)
{
    rotate_z(&(player->view), -player->rot_speed);
	rotate_z(&(player->dir), -player->rot_speed);
}

static void    apply_move_forvard(t_player *player, char **map)
{
    double  new_pos_x;
    double  new_pos_y;
    double  pos_x;
    double  pos_y;

    pos_x = player->pos.x;
    pos_y = player->pos.y;

    new_pos_x = pos_x + player->dir.x * EPSILON * player->move_speed;
    new_pos_y = pos_y + player->dir.y * EPSILON * player->move_speed;
    ///
}

static void    apply_move_back(t_player *player, char **map)
{

    double  new_pos_x;
    double  new_pos_y;
    double  pos_x;
    double  pos_y;

    pos_x = player->pos.x;
    pos_y = player->pos.y;

    new_pos_x = pos_x - player->dir.x * player->move_speed;
    new_pos_y = pos_y - player->dir.y * player->move_speed;
    ///
}

void    apply_controls(t_player *player, char **map)
{
    if (player->move_forw) {
		apply_move_forvard(player, map);
    }
	if (player->move_back) {
		apply_move_back(player, map);
    }
	if (player->rot_left) {
        apply_rot_left(player);
    }
	if (player->rot_right) {
        apply_rot_right(player);
    }
}


void test_controls(t_player *player, char **map) {
    (void)map;
    if (player->move_forw) {
		player->pos.y += 1;
    }
	if (player->move_back) {
		player->pos.y -= 1;
    }
	if (player->rot_left) {
        player->pos.x += 1;
    }
	if (player->rot_right) {
        player->pos.x -= 1;
    }
}
