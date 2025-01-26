#include "../../includes/cub3d.h"

void	enqueue(t_queue **queue, int x, int y)
{
	t_queue	*new;
	t_queue	*temp;

	new = gc_malloc(sizeof(t_queue));
	new->x = x;
	new->y = y;
	new->next = NULL;
	if (!(*queue))
		*queue = new;
	else
	{
		temp = *queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	dequeue(t_queue **queue)
{
	t_queue	*temp;

	if (!(*queue))
		return ;
	temp = *queue;
	*queue = (*queue)->next;
	gc_free_ptr(temp);
}

static bool	**create_visited(int height, int width)
{
	int		i;
	int		j;
	bool	**visited;

	visited = gc_malloc(height * sizeof(bool *));
	i = 0;
	while (i < height)
	{
		visited[i] = gc_malloc(width * sizeof(bool));
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
		gc_free_ptr(visited[i]);
		i++;
	}
	gc_free_ptr(visited);
}

static bool	is_on_edge(int x, int y, int width, int height)
{
	return (x == 0 || x == width - 1 || y == 0 || y == height - 1);
}

static void	process_neighbors(int x, int y, t_queue **queue, char **map,
		bool **visited, int width, int height)
{
	const int	directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int			d;
	int			nx;
	int			ny;

	d = 0;
	while (d < 4)
	{
		nx = x + directions[d][0];
		ny = y + directions[d][1];
		if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
			map[ny][nx] != '1' && !visited[ny][nx])
		{
			visited[ny][nx] = true;
			enqueue(queue, nx, ny);
		}
		d++;
	}
}

bool	flood_fill(char **map, int width, int height, int start_x, int start_y)
{
	bool	**visited;
	t_queue	*queue;
	int		x;
	int		y;

	visited = create_visited(height, width);
	queue = NULL;
	enqueue(&queue, start_x, start_y);
	visited[start_y][start_x] = true;
	while (queue)
	{
		x = queue->x;
		y = queue->y;
		dequeue(&queue);
		if (is_on_edge(x, y, width, height))
		{
			free_visited(visited, height);
			return (true);
		}
		process_neighbors(x, y, &queue, map, visited, width, height);
	}
	free_visited(visited, height);
	return (false);
}
