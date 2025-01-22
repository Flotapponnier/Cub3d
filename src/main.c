#include "../includes/cub3d.h"


int main(void)
{
	t_game game;
	
	init_game(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	draw_square(WIDTH / 2 - 10, HEIGHT / 2 - 10, 20, 0x00FF00FF, &game);
	mlx_loop(game.mlx);
}

