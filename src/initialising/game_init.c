#include "../../includes/cub3d.h"

void init_player(t_player *player)
{
    player->key_up = false;
    player->key_down = false;
    player->key_right = false;
    player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void print_map(char **map)
{
    int i = 0;

    if (!map)
    {
        printf("Map is NULL\n");
        return;
    }

    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}

int init_game(t_game *game, char *path_user_input)
{
	if(init_map(game, path_user_input) == 1)
		destroy_cub3d(NULL, 1);
	print_map(game->map);
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
