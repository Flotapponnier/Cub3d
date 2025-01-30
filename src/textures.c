/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:28 by dilin             #+#    #+#             */
/*   Updated: 2025/01/30 20:15:43 by dilin            ###   ########.fr       */
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
    int x = (int)(tex_x * tex->width);
    int y = (int)(tex_y * tex->height);
    
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= tex->width) x = tex->width - 1;
    if (y >= tex->height) y = tex->height - 1;
    
    return tex->pixels[y * tex->width + x];
}

void free_textures(t_game *game)
{
    for (int i = 0; i < 4; i++)
    {
        if (game->textures[i].texture)
            mlx_delete_texture(game->textures[i].texture);
    }
}