#include "../../includes/cub3d.h"

static void handle_key_press(struct mlx_key_data keydata, t_player *player)
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

static void handle_key_release(struct mlx_key_data keydata, t_player *player)
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

void key_hook(struct mlx_key_data keydata, void *param)
{
    t_game *game = (t_game *)param;
    t_player *player = &game->player;

    if (keydata.action == MLX_PRESS)
        handle_key_press(keydata, player);
    if (keydata.action == MLX_RELEASE)
        handle_key_release(keydata, player);
}
