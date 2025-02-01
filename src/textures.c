/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:28 by dilin             #+#    #+#             */
/*   Updated: 2025/02/01 16:53:13 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int load_texture(t_game *game, t_texture *tex, char *path)
{
	(void)game;
    tex->texture = mlx_load_png(path);
    if (!tex->texture)
        return (error("Failed to load texture"));
    
    tex->width = tex->texture->width;
    tex->height = tex->texture->height;
    tex->pixels = (uint32_t *)tex->texture->pixels;
    
    return (0);
}

int load_all_textures(t_game *game)
{
    if (load_texture(game, &game->textures[0], game->map_struct.path_north) ||
        load_texture(game, &game->textures[1], game->map_struct.path_south) ||
        load_texture(game, &game->textures[2], game->map_struct.path_west) ||
        load_texture(game, &game->textures[3], game->map_struct.path_east))
        return (1);
    return (0);
}

uint32_t get_texture_color(t_texture *tex, float tex_x, float tex_y)
{
    // Ensure texture coordinates are within bounds
    tex_x = fmod(tex_x, 1.0);
    tex_y = fmod(tex_y, 1.0);
    
    if (tex_x < 0) tex_x += 1.0;
    if (tex_y < 0) tex_y += 1.0;

    // Convert to pixel coordinates
    int x = (int)(tex_x * tex->width);
    int y = (int)(tex_y * tex->height);
    
    // Clamp values
    x = x < 0 ? 0 : x >= tex->width ? tex->width - 1 : x;
    y = y < 0 ? 0 : y >= tex->height ? tex->height - 1 : y;

    uint32_t color = tex->pixels[y * tex->width + x];
    uint8_t a = (color >> 24) & 0xFF;
    uint8_t b = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t r = color & 0xFF;

    return (r << 24) | (g << 16) | (b << 8) | a;
}

void free_textures(t_game *game)
{
    for (int i = 0; i < 4; i++)
    {
        if (game->textures[i].texture)
            mlx_delete_texture(game->textures[i].texture);
    }
}