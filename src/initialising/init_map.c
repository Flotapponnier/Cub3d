/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:33 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/03 21:44:22 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_map_info_complete(t_map *map_struct)
{
	return (map_struct->path_north && map_struct->path_south
		&& map_struct->path_west && map_struct->path_east
		&& map_struct->color_floor && map_struct->color_cell);
}

static int	handle_empty_line(char *line)
{
	if (*line == '\n' || *line == '\0')
	{
		gc_free_ptr(line);
		return (1);
	}
	return (0);
}

int	extract_info(t_map *map_struct, int fd)
{
	char	*line;

	line = gc_add(get_next_line(fd));
	while (line != NULL)
	{
		if (handle_empty_line(line))
		{
			line = gc_add(get_next_line(fd));
			continue ;
		}
		if (process_map_metadata(map_struct, line))
		{
			gc_free_ptr(line);
			return (error("Invalid character in map header"));
		}
		gc_free_ptr(line);
		if (is_map_info_complete(map_struct))
			return (0);
		line = gc_add(get_next_line(fd));
	}
	return (error("Missing map textures or colors"));
}

/* void	print_map_struct(t_map *map_struct)
{
	if (!map_struct)
	{
		printf("Map struct is NULL\n");
		return ;
	}
	printf("=== MAP STRUCT CONTENT ===\n");
	printf("North Texture Path : %s\n",
		map_struct->path_north ? map_struct->path_north : "Not set");
	printf("South Texture Path : %s\n",
		map_struct->path_south ? map_struct->path_south : "Not set");
	printf("West Texture Path  : %s\n",
		map_struct->path_west ? map_struct->path_west : "Not set");
	printf("East Texture Path  : %s\n",
		map_struct->path_east ? map_struct->path_east : "Not set");
	printf("Floor Color        : %s\n",
		map_struct->color_floor ? map_struct->color_floor : "Not set");
	printf("Ceiling Color      : %s\n",
		map_struct->color_cell ? map_struct->color_cell : "Not set");
	printf("Map Width          : %d\n", map_struct->map_width);
	printf("Map Height         : %d\n", map_struct->map_height);
	if (map_struct->map)
	{
		printf("Map Data:\n");
		for (int i = 0; map_struct->map[i]; i++)
			printf("%s\n", map_struct->map[i]);
	}
	else
		printf("Map Data           : Not set\n");
	printf("==========================\n");
} */

static int	init_map_data(t_game *game, int fd)
{
	t_map_node	*map_list;

	if (extract_info(&game->map_struct, fd))
		return (1);
	map_list = load_map(fd);
	if (!map_list)
		return (error("Failed to load map"));
	if (process_map_data(game, map_list))
		return (1);
	free_map_list(map_list);
	return (0);
}

int	init_map(t_game *game, char *path_user_input)
{
	int	fd;

	game->map_struct.map_width = 0;
	game->map_struct.map_height = 0;
	ft_bzero(&game->map_struct, sizeof(t_map));
	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4,
			4) != 0)
		return (error(ERROR_EXTENSION));
	fd = gc_add_fd(open(path_user_input, O_RDONLY));
	if (fd < 0)
		return (error(ERROR_FD));
	if (init_map_data(game, fd))
		return (1);
	game->floor_color = convert_rgb_to_uint(game->map_struct.color_floor);
	game->ceiling_color = convert_rgb_to_uint(game->map_struct.color_cell);
	return (0);
}
