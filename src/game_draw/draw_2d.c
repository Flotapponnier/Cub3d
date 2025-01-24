#include "../../includes/cub3d.h"

void draw_map(t_game *game)
{
    char **map = game->map;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, SQUARE2D_COLOR, game);
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

void draw_raycast_line(mlx_image_t *image, uint32_t ray_x, uint32_t ray_y, uint32_t color)
{
    mlx_put_pixel(image, ray_x, ray_y, color);
}
