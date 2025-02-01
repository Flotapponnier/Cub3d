/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 16:40:05 by dilin            ###   ########.fr       */
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
        mlx_put_pixel(game->img, i, j, game->floor_color);
        j++;
    }
}

void draw_ceiling_slice(t_game *game, int i, int ceiling_end)
{
    int j = 0;
    while (j < ceiling_end)
    {
        mlx_put_pixel(game->img, i, j, game->ceiling_color);
        j++;
    }
}

void draw_3d_monitor(t_game *game, int x)
{
    // Fix fisheye effect by using perpendicular distance
    double perp_wall_dist;
    if (game->ray.side == 0)
        perp_wall_dist = (game->ray.map_x - game->player.x / 64.0 + 
            (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
    else
        perp_wall_dist = (game->ray.map_y - game->player.y / 64.0 + 
            (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;

    // Calculate wall height with proper scaling
    int line_height = (int)(HEIGHT / perp_wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    int draw_start = -line_height / 2 + HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT)
        draw_end = HEIGHT - 1;

    // Draw ceiling
    draw_ceiling_slice(game, x, draw_start);

    // Calculate wall X coordinate where ray hit
    double wall_x;
    if (game->ray.side == 0)
        wall_x = game->player.y / 64.0 + perp_wall_dist * game->ray.ray_dir_y;
    else
        wall_x = game->player.x / 64.0 + perp_wall_dist * game->ray.ray_dir_x;
    wall_x -= floor(wall_x);

    // Draw wall with texture
    int tex_num;
    if (game->ray.direction == 'N') tex_num = 0;
    else if (game->ray.direction == 'S') tex_num = 1;
    else if (game->ray.direction == 'W') tex_num = 2;
    else tex_num = 3;

    float step = 1.0 * game->textures[tex_num].height / line_height;
    float tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
    
    // Draw the wall line
    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (game->textures[tex_num].height - 1);
        tex_pos += step;
        uint32_t color = get_texture_color(&game->textures[tex_num], wall_x, 
            (float)tex_y / game->textures[tex_num].height);
        mlx_put_pixel(game->img, x, y, color);
    }

    // Draw floor
    draw_floor_slice(game, x, draw_end);
}
