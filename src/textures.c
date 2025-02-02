/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:52:28 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 19:28:35 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_texture(t_game *game, t_texture *tex, char *path)
{
	(void)game;
	tex->texture = gc_add(mlx_load_png(path));
	if (!tex->texture)
		return (error("Failed to load texture"));
	tex->width = tex->texture->width;
	tex->height = tex->texture->height;
	tex->pixels = (uint32_t *)tex->texture->pixels;
	return (0);
}

int	load_all_textures(t_game *game)
{
	if (load_texture(game, &game->textures[0], game->map_struct.path_north)
		|| load_texture(game, &game->textures[1], game->map_struct.path_south)
		|| load_texture(game, &game->textures[2], game->map_struct.path_west)
		|| load_texture(game, &game->textures[3], game->map_struct.path_east))
		return (1);
	return (0);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].texture)
			mlx_delete_texture(game->textures[i].texture);
		i++;
	}
}
