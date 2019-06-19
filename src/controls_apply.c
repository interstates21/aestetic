#include "alt.h"

static void    apply_rot_left(t_player *player)
{
    player->cam = rotate_z(player->cam, player->rot_speed);
	player->dir = rotate_z(player->dir, player->rot_speed);
}

static void    apply_rot_right(t_player *player)
{
    player->cam = rotate_z(player->cam, -player->rot_speed);
	player->dir = rotate_z(player->dir, -player->rot_speed);
}

static void    apply_move_forvard(t_player *player, char **map)
{
    double  new_pos_x;
    double  new_pos_y;
    double  pos_x;
    double  pos_y;
    // todo: define as const

    pos_x = player->pos.x;
    pos_y = player->pos.y;
    new_pos_x = pos_x + player.dir.x * player.move_speed;
    new_pos_y = pos_y + player.dir.y * player.move_speed;
    if /* Exists */ (map[(int)pos_y][(int)new_pos_x])
    {
        if /* Is walkable */ (map[(int)pos_y][(int)new_pos_x] == '0')
		    player->pos.x = new_pos_x;
    }
    if (map[(int)new_pos_y][(int)pos_x])
    {
        if (map[(int)new_pos_y][(int)pos_x] == '0')
		    player->pos.y = new_pos_y;
    }
}

static void    apply_move_back(t_player *player)
{
    double  new_pos_x;
    double  new_pos_y;
    double  pos_x;
    double  pos_y;
    // todo: define as const

    pos_x = player->pos.x;
    pos_y = player->pos.y;
    new_pos_x = pos_x - player.dir.x * player.move_speed;
    new_pos_y = pos_y - player.dir.y * player.move_speed;
    if (map[(int)pos_y][(int)new_pos_x]) // EXISTS
    {
        if (map[(int)pos_y][(int)new_pos_x] == '0')// IS WALKABLE
		    player->pos.x = new_pos_x;
    }
    if (map[(int)new_pos_y][(int)pos_x])
    {
        if (map[(int)new_pos_y][(int)pos_x] == '0')
		    player->pos.y = new_pos_y;
    }
}

void    apply_controls(t_player *player, char **map)
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