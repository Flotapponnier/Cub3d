/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 18:49:31 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

void draw_wall_slice(t_game *game, uint32_t i, float start_y, float end, uint32_t color)
{
    while (start_y < end)
    {
        mlx_put_pixel(game->img, i, (int)start_y, color);
        start_y++;
    }
}

void draw_floor_slice(t_game *game, int i, int start_y)
{
    int j = start_y;
    while (j < HEIGHT)
    {
        mlx_put_pixel(game->img, i, j, FLOOR_COLOR);
        j++;
    }
}

void draw_ceiling_slice(t_game *game, int i, int ceiling_end)
{
    int j = 0;
    while (j < ceiling_end)
    {
        mlx_put_pixel(game->img, i, j, CEILING_COLOR);
        j++;
    }
}
