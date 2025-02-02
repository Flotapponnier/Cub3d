/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture_validator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:50:45 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 17:46:27 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	validate_texture_path(const char *path)
{
	int		fd;
	size_t	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (false);
	}
	close(fd);
	len = ft_strlen(path);
	return (len > 4 && ft_strncmp(path + len - 4, ".png", 4) == 0);
}

static bool	is_valid_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	return (true);
}

static void	free_rgb_array(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		gc_free_ptr(rgb[i]);
		i++;
	}
	gc_free_ptr(rgb);
}

static bool	is_valid_rgb(const char *color_str)
{
	char	**rgb;
	bool	valid;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		gc_free_ptr(rgb);
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	valid = is_valid_rgb_values(r, g, b);
	free_rgb_array(rgb);
	return (valid);
}

bool	validate_map_textures_colors(t_map *map_struct)
{
	if (!map_struct->path_north || !map_struct->path_south
		|| !map_struct->path_west || !map_struct->path_east
		|| !map_struct->color_floor || !map_struct->color_cell)
		return (false);
	if (!validate_texture_path(map_struct->path_north)
		|| !validate_texture_path(map_struct->path_south)
		|| !validate_texture_path(map_struct->path_west)
		|| !validate_texture_path(map_struct->path_east))
		return (false);
	if (!is_valid_rgb(map_struct->color_floor)
		|| !is_valid_rgb(map_struct->color_cell))
		return (false);
	return (true);
}
