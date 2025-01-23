#include "../../includes/cub3d.h"

void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0x0000FF;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void draw_loop(void *param)
{
    t_game *game = (t_game *)param;
    t_player *player = &game->player;
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, SIZE_PLAYER, 0x00FF00FF, game);
	draw_map(game);

	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	while(!touch(ray_x, ray_y, game))
	{
		mlx_put_pixel(game->img, ray_x, ray_y, 0x00FF00FF);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	int i = -1;
	
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y, color);
	i = - 1;
	while (++i < size)
		mlx_put_pixel(game->img, x, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + size, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y + size, color);
}
