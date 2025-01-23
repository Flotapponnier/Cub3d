#include "../includes/cub3d.h"




void clear_image(t_game *game)
{
    if (!game->img || !game->img->pixels)
        return;
    bzero(game->img->pixels, game->img->width * game->img->height * sizeof(int));
}


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

int main(void)
{
	t_game game;
	
	init_game(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
}

