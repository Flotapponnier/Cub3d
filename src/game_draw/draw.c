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

	player = &game->player;

	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, SIZE_PLAYER, 0x00FF00FF, game);
	draw_map(game);
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
