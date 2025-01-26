/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:50 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/26 13:37:56 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	map = game->map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, SQUARE2D_COLOR, game);
			x++;
		}
		y++;
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + size, y + i, color);
	i = -1;
	while (++i < size)
		mlx_put_pixel(game->img, x + i, y + size, color);
}

void	draw_raycast_line(mlx_image_t *image, uint32_t ray_x, uint32_t ray_y,
		uint32_t color)
{
	mlx_put_pixel(image, ray_x, ray_y, color);
}
