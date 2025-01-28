/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:33 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/28 17:49:16 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_map_node	*add_map_node(t_map_node **head, char *line)
{
	t_map_node	*new_node;
	t_map_node	*temp;

	new_node = gc_malloc(sizeof(t_map_node));
	if (!new_node)
		return (NULL);
	new_node->line = line;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}

static t_map_node	*load_map(int fd)
{
	t_map_node	*map_list;
	char		*line;

	map_list = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!add_map_node(&map_list, line))
		{
			gc_free_ptr(line);
			return (NULL);
		}
	}
	return (map_list);
}

char	**get_map(t_map_node *map_list)
{
	int			line_count;
	t_map_node	*temp;
	char		**map;
	int			i;
	int			len;

	line_count = 0;
	temp = map_list;
	while (temp)
	{
		line_count++;
		temp = temp->next;
	}
	map = gc_malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	temp = map_list;
	i = 0;
	while (temp)
	{
		map[i] = ft_strdup(temp->line);
		if (!map[i])
			return (NULL);
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		temp = temp->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

int extract_info(t_map *map_struct, int fd)
{
    char *line;


    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n' || *line == '\0')
        {
            gc_free_ptr(line);
            continue;
        }
        if (!ft_strncmp(line, "NO ", 3) && !map_struct->path_north)
            map_struct->path_north = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "SO ", 3) && !map_struct->path_south)
            map_struct->path_south = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "WE ", 3) && !map_struct->path_west)
            map_struct->path_west = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "EA ", 3) && !map_struct->path_east)
            map_struct->path_east = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "F ", 2) && !map_struct->color_floor)
            map_struct->color_floor = ft_strtrim(line + 2, " \n");
        else if (!ft_strncmp(line, "C ", 2) && !map_struct->color_cell)
            map_struct->color_cell = ft_strtrim(line + 2, " \n");
        else
        {
            gc_free_ptr(line);
            return error("Invalid character in map header");
        }
        gc_free_ptr(line);
        if (map_struct->path_north && map_struct->path_south &&
            map_struct->path_west && map_struct->path_east &&
            map_struct->color_floor && map_struct->color_cell)
        {
            return (0);
        }
    }

    return error("Missing map textures or colors");
}

void print_map_struct(t_map *map_struct)
{
    if (!map_struct)
    {
        printf("Map struct is NULL\n");
        return;
    }

    printf("=== MAP STRUCT CONTENT ===\n");
    printf("North Texture Path : %s\n", map_struct->path_north ? map_struct->path_north : "Not set");
    printf("South Texture Path : %s\n", map_struct->path_south ? map_struct->path_south : "Not set");
    printf("West Texture Path  : %s\n", map_struct->path_west ? map_struct->path_west : "Not set");
    printf("East Texture Path  : %s\n", map_struct->path_east ? map_struct->path_east : "Not set");
    printf("Floor Color        : %s\n", map_struct->color_floor ? map_struct->color_floor : "Not set");
    printf("Ceiling Color      : %s\n", map_struct->color_cell ? map_struct->color_cell : "Not set");
    printf("Map Width          : %d\n", map_struct->map_width);
    printf("Map Height         : %d\n", map_struct->map_height);

    if (map_struct->map)
    {
        printf("Map Data:\n");
        for (int i = 0; map_struct->map[i]; i++)
            printf("%s\n", map_struct->map[i]);
    }
    else
    {
        printf("Map Data           : Not set\n");
    }
    printf("==========================\n");
}

int	init_map(t_game *game, char *path_user_input)
{
	int			fd;
	t_map_node	*map_list;
	int map_width;
	int map_height;

	map_width = 0;
	map_height = 0;
	ft_bzero(&game->map_struct, sizeof(t_map));
	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4,
			4) != 0)
		return (error(ERROR_EXTENSION));
	fd = gc_add_fd(open(path_user_input, O_RDONLY));
	if (fd < 0)
		return (error(ERROR_FD));
	if(extract_info(&game->map_struct, fd))
		return (1);
	print_map_struct(&game->map_struct);
	map_list = load_map(fd);
	if (!map_list)
		return (error("Failed to load map"));
	if (check_map(map_list, &game->player, &map_width, &map_height) == 1)
		return (1);
	game->map = get_map(map_list);
	printf("Map width : %d \n, Map height %d \n", map_width, map_height);
	int result = flood_fill(game->map, map_width, map_height, (int)game->player.x, (int)game->player.y);
	if (result)
	{
		print_map(game->map);	
		return error("Map is not enclosed!\n");
	}
	else
		printf("Map is fully enclosed by walls.\n");
	return (0);
}
