#include "../../includes/cub3d.h"

void init_player(t_player *player)
{
	player->angle = PI / 2;
    player->x = (float)WIDTH / 2;
    player->y = (float)HEIGHT / 2;
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

char **get_map(void)
{
    char **map = gc_malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
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

int init_game(t_game *game, char *path_user_input)
{
	if(init_map(game, path_user_input) == 1)
		destroy_cub3d(NULL, 1);
	game->map = get_map();
	init_player(&game->player);
	game->mlx = mlx_init(WIDTH, HEIGHT, "mlx", true);
	if(!game->mlx)
		destroy_cub3d(NULL, 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if(!game->img)
		destroy_cub3d(game->mlx, 1);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	return (1);
}
