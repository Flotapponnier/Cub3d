#include "../../includes/cub3d.h"

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

static float fixed_distance(float x1, float y1, float x2, float y2, t_game *game)
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

void draw_wall_3d(t_game *game, uint32_t i, uint32_t ray_x, uint32_t ray_y, t_player *player)
{
    float dist = fixed_distance(player->x, player->y, ray_x, ray_y, game);
    if (dist <= 0)
        dist = 0.0001f;
    float height = (BLOCK / dist) * ((float)WIDTH / 2);
    float start_y = (HEIGHT - height) / 2;
    float end = start_y + height;
    if (end >= HEIGHT)
        end = HEIGHT - 1;
    while (start_y < end)
    {
        mlx_put_pixel(game->img, (int)i, (int)start_y, 0x00FF00FF);
        start_y++;
    }
}
