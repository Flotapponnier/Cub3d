#include "../../includes/cub3d.h"


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
