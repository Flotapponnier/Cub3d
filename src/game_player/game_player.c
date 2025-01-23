#include "../../includes/cub3d.h"

void move_player(t_player *player)
{
	int speed;

	speed = 5;
	if(player->key_up)
		player->y -= speed;
	if(player->key_down)
		player->y += speed;
	if(player->key_left)
		player->x -= speed;
	if(player->key_right)
		player->x += speed;
}
