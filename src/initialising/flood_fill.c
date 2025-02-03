/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:23 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/03 18:41:36 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	**create_visited(int height, int width)
{
	int		i;
	int		j;
	bool	**visited;

	visited = malloc(height * sizeof(bool *));
	i = 0;
	while (i < height)
	{
		visited[i] = malloc(width * sizeof(bool));
		j = 0;
		while (j < width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
	return (visited);
}

static void	free_visited(bool **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static bool	is_on_edge(int x, int y, int width, int height)
{
	return (x == 0 || x == width - 1 || y == 0 || y == height - 1);
}

static void	process_neighbors(t_pos pos, t_queue **queue, t_map_data *map_data)
{
	const int	directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int			d;
	t_pos		new_pos;

	d = 0;
	while (d < 4)
	{
		new_pos.x = pos.x + directions[d][0];
		new_pos.y = pos.y + directions[d][1];
		if (new_pos.x >= 0 && new_pos.x < map_data->width && new_pos.y >= 0
			&& new_pos.y < map_data->height
			&& map_data->map[new_pos.y][new_pos.x] != '1'
			&& !map_data->visited[new_pos.y][new_pos.x])
		{
			map_data->visited[new_pos.y][new_pos.x] = true;
			enqueue(queue, new_pos.x, new_pos.y);
		}
		d++;
	}
}

bool	flood_fill(char **map, int width, int height, t_pos start)
{
	t_map_data	map_data;
	t_queue		*queue;
	t_pos		current;

	map_data.map = map;
	map_data.width = width;
	map_data.height = height;
	map_data.visited = create_visited(height, width);
	queue = NULL;
	enqueue(&queue, start.x, start.y);
	map_data.visited[start.y][start.x] = true;
	while (queue)
	{
		current.x = queue->x;
		current.y = queue->y;
		dequeue(&queue);
		if (is_on_edge(current.x, current.y, width, height))
		{
			free_visited(map_data.visited, height);
			return (true);
		}
		process_neighbors(current, &queue, &map_data);
	}
	free_visited(map_data.visited, height);
	return (false);
}
