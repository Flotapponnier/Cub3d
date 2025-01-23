#include "../includes/cub3d.h"


void handle_key_press(struct mlx_key_data keydata, t_player *player)
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

void handle_key_release(struct mlx_key_data keydata, t_player *player)
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

void move_player(t_player *player)
{
	int speed;

	speed = 5;
	if(player->key_up)
		player->y -= speed;
	if(player->key_down)
		player->y += speed;
	if(player->key_left)
		player->x -= speed;
	if(player->key_right)
		player->x += speed;
}

void init_player(t_player *player)
{
    player->x = (float)WIDTH / 2;
    player->y = (float)HEIGHT / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "10000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
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
