/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:06:32 by dilin             #+#    #+#             */
/*   Updated: 2025/02/03 18:03:46 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	**allocate_map(int line_count)
{
	char	**map;

	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	return (map);
}

static int	fill_map_lines(char **map, t_map_node *map_list)
{
	t_map_node	*temp;
	int			i;

	temp = map_list;
	i = 0;
	while (temp)
	{
		map[i] = ft_strdup(temp->line);
		if (!map[i])
			return (0);
		clean_newline(map[i]);
		temp = temp->next;
		i++;
	}
	map[i] = NULL;
	return (1);
}

char	**get_map(t_map_node *map_list)
{
	char	**map;
	int		line_count;

	line_count = count_map_lines(map_list);
	map = allocate_map(line_count);
	if (!map)
		return (NULL);
	if (!fill_map_lines(map, map_list))
		return (NULL);
	return (map);
}

