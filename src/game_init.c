#include "../includes/cub3d.h"

void key_hook(struct mlx_key_data keydata, void *param)
{
    t_game *game = (t_game *)param;
    t_player *player = &game->player;

    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_W)
		{
			printf(" W pressed\n");
            player->key_up = true;
		}
        if (keydata.key == MLX_KEY_S)
            player->key_down = true;
        if (keydata.key == MLX_KEY_A)
            player->key_left = true;
        if (keydata.key == MLX_KEY_D)
            player->key_right = true;
    }
    if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W)
		{
			printf("W Released \n");
            player->key_up = false;
		}
        if (keydata.key == MLX_KEY_S)
            player->key_down = false;
        if (keydata.key == MLX_KEY_A)
            player->key_left = false;
        if (keydata.key == MLX_KEY_D)
            player->key_right = false;
    }
}

/*
void key_press(void *param)
{
	t_game *game= (t_game*)param;
	t_player player = game->player;
    if(mlx_is_key_down(game->mlx, MLX_KEY_W))
        player.key_up = true;
    if(mlx_is_key_down(game->mlx, MLX_KEY_S))
        player.key_down = true;
    if(mlx_is_key_down(game->mlx, MLX_KEY_A))
        player.key_left = true;
    if(mlx_is_key_down(game->mlx, MLX_KEY_D))
        player.key_right = true;
}
*/
void init_player(t_player *player)
{
    player->x = (float)WIDTH / 2;
    player->y = (float)HEIGHT / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
}

void init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init(WIDTH, HEIGHT, "mlx", true);
	if(!game->mlx)
		exit(1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if(!game->img)
	{
		mlx_close_window(game->mlx);
		exit(1);
	}
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
