/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:06:39 by dilin             #+#    #+#             */
/*   Updated: 2025/02/03 18:10:45 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_map_node	*add_map_node(t_map_node **head, char *line)
{
	t_map_node	*new_node;
	t_map_node	*temp;

	new_node = malloc(sizeof(t_map_node));
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

t_map_node	*load_map(int fd)
{
	t_map_node	*map_list;
	char		*line;

	map_list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!add_map_node(&map_list, line))
		{
			free(line);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (map_list);
}

void	clean_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	count_map_lines(t_map_node *map_list)
{
	int			count;
	t_map_node	*temp;

	count = 0;
	temp = map_list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	process_map_metadata(t_map *map_struct, char *line)
{
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
		return (1);
	return (0);
}
