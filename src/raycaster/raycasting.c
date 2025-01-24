#include "../../includes/cub3d.h"

static float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_distance(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x;
	float delta_y;
	float angle;
	float fixed_distance;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fixed_distance = distance(delta_x, delta_y) * cos(angle);
	return (fixed_distance);
}

