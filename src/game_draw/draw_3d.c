/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 19:52:50 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

void draw_wall_slice(t_game *game, uint32_t i, float start_y, float wall_height,
                    float ray_x, float ray_y, char direction)
{
    int tex_index;
    float tex_x;
    
    // Determine which texture to use based on wall direction
    switch(direction)
    {
        case 'N': tex_index = 0; break;
        case 'S': tex_index = 1; break;
        case 'W': tex_index = 2; break;
        case 'E': tex_index = 3; break;
        default: return;
    }
    
    // Calculate texture X coordinate
    if (direction == 'N' || direction == 'S')
        tex_x = fmod(ray_x, BLOCK) / BLOCK;
    else
        tex_x = fmod(ray_y, BLOCK) / BLOCK;
    
    // Fix texture mirroring
    if (direction == 'N' || direction == 'W')
        tex_x = 1.0f - tex_x;
    
    float step = 1.0f / wall_height;
    float tex_pos = 0;
    
    if (start_y < 0)
    {
        tex_pos = -start_y * step;
        start_y = 0;
    }
    
    float end = start_y + wall_height;
    if (end >= HEIGHT)
        end = HEIGHT - 1;
    
    while (start_y < end)
    {
        uint32_t color = get_texture_color(&game->textures[tex_index], tex_x, tex_pos);
        mlx_put_pixel(game->img, i, (int)start_y, color);
        tex_pos += step;
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
