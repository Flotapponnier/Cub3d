/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/28 19:35:03 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_wall_slice(t_game *game, uint32_t i, float start_y, float end)
{
    while (start_y < end)
    {
        mlx_put_pixel(game->img, i, (int)start_y, SQUARE3D_COLOR);
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
