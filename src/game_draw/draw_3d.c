#include "../../includes/cub3d.h"

void	draw_wall_3d(t_game *game, uint32_t i, uint32_t ray_x, uint32_t ray_y,
		t_player *player)
{
	float	dist;
	float	start_y;
	float	height;
	float	end;

	dist = fixed_distance(player->x, player->y, ray_x, ray_y, game);
	height = (BLOCK / dist) * ((float)WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (dist <= 0)
		dist = 0.0001f;
	if (start_y < 0)
		start_y = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start_y < end)
	{
		mlx_put_pixel(game->img, (int)i, (int)start_y, SQUARE3D_COLOR);
		start_y++;
	}
}
