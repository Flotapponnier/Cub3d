#include "../includes/cub3d.h"




void clear_image(t_game *game)
{
    if (!game->img || !game->img->pixels)
        return;
    bzero(game->img->pixels, game->img->width * game->img->height * sizeof(int));
}

void draw_loop(void *param)
{

    t_game *game = (t_game *)param;
    t_player *player = &game->player;

	player = &game->player;

	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 5, 0x00FF00FF, game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

int main(void)
{
	t_game game;
	
	init_game(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}

