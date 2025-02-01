/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:28 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 20:38:53 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	player->x = (player->x * 64) + 32;
	player->y = (player->y * 64) + 32;
}

int	init_game(t_game *game, char *path_user_input)
{
	if (init_map(game, path_user_input) == 1)
		destroy_cub3d(NULL, 1);
	print_map(game->map);
	init_player(&game->player);
	game->debug_view = false;
	game->mlx = mlx_init(WIDTH, HEIGHT, "mlx", false);
	if (!game->mlx)
		destroy_cub3d(NULL, 1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		destroy_cub3d(game->mlx, 1);
	if (load_all_textures(game))
	{
		free_textures(game);
		destroy_cub3d(game->mlx, 1);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		destroy_cub3d(game->mlx, 1);
	return (1);
}
