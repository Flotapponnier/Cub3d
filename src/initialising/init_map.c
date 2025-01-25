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

int	init_map(t_game *game, char *path_user_input)
{
	int			fd;
	t_map_node	*map_list;

	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4,
			4) != 0)
		return (error(ERROR_EXTENSION));
	fd = gc_add_fd(open(path_user_input, O_RDONLY));
	if (fd < 0)
		return (error(ERROR_FD));
	map_list = load_map(fd);
	if (!map_list)
		return (error("Failed to load map"));
	if (check_map(map_list, &game->player) == 1)
		return (1);
	game->map = get_map(map_list);
	return (0);
}
