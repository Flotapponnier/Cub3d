/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:50 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/02 15:08:32 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	char			**map;
	int				y;
	int				x;
	t_square_params	params;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				params.x = x * BLOCK;
				params.y = y * BLOCK;
				params.size = BLOCK;
				params.color = SQUARE2D_COLOR;
				draw_square(params, game);
			}
			x++;
		}
		y++;
	}
}

void	draw_square(t_square_params params, t_game *game)
{
	int	i;

	i = -1;
	while (++i < params.size)
		mlx_put_pixel(game->img, params.x + i, params.y, params.color);
	i = -1;
	while (++i < params.size)
		mlx_put_pixel(game->img, params.x, params.y + i, params.color);
	i = -1;
	while (++i < params.size)
		mlx_put_pixel(game->img, params.x + params.size, params.y + i,
			params.color);
	i = -1;
	while (++i < params.size)
		mlx_put_pixel(game->img, params.x + i, params.y + params.size,
			params.color);
}
