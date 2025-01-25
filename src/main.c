#include "../includes/cub3d.h"


int main(int argc , char **argv)
{
	t_game game;
	
	if(argc != 2)
		return (error(ERROR_ARG), 1);
	init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

