/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:38 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/04 19:13:54 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	handle_key_press(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player.key_up = true;
	if (keydata.key == MLX_KEY_S)
		game->player.key_down = true;
	if (keydata.key == MLX_KEY_A)
		game->player.key_left = true;
	if (keydata.key == MLX_KEY_D)
		game->player.key_right = true;
	if (keydata.key == MLX_KEY_LEFT)
		game->player.left_rotate = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player.right_rotate = true;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		free_map(game->map);
		destroy_cub3d(game->mlx, 0);
	}
}

static void	handle_key_release(struct mlx_key_data keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W)
		game->player.key_up = false;
	if (keydata.key == MLX_KEY_S)
		game->player.key_down = false;
	if (keydata.key == MLX_KEY_A)
		game->player.key_left = false;
	if (keydata.key == MLX_KEY_D)
		game->player.key_right = false;
	if (keydata.key == MLX_KEY_LEFT)
		game->player.left_rotate = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->player.right_rotate = false;
}

void	key_hook(struct mlx_key_data keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS)
		handle_key_press(keydata, game);
	if (keydata.action == MLX_RELEASE)
		handle_key_release(keydata, game);
}
