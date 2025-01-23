#include "../../includes/cub3d.h"

bool touch(float px, float py, t_game *game)
{
	int x;
	int y;

	x = px / BLOCK;
	y = py / BLOCK;
	if(game->map[y][x] == '1')
		return (true);
	return (false);
}
