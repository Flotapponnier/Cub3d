/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:28 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/26 13:32:29 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void init_player(t_player *player)
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
