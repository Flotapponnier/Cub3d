#include "../../includes/cub3d.h"


static int check_map(t_map_node *map_list, t_player *player)
{
    int i, row = 0;
    int player_count = 0;
    t_map_node *temp = map_list;

    while (temp)
    {
        i = 0;
        while (temp->line[i] != '\0')
        {
            if (temp->line[i] == '1' || temp->line[i] == '0' || temp->line[i] == ' ' || temp->line[i] == '\n')
                i++;
            else if (temp->line[i] == 'N' || temp->line[i] == 'S' || temp->line[i] == 'W' || temp->line[i] == 'E')
            {
                player_count++;
                if (player_count > 1)
                    return (error("More than one player on the map"));
                player->x = (i * 64) + 32;
                player->y = (row * 64) + 32;
                if (temp->line[i] == 'N')
                    player->angle = 3 * PI / 2;
                else if (temp->line[i] == 'S')
                    player->angle = PI / 2;
                else if (temp->line[i] == 'W')
                    player->angle = PI;
                else if (temp->line[i] == 'E')
                    player->angle = 0;
                i++;
            }
            else
                return (error(ERROR_WRONG_CHAR));
        }
        temp = temp->next;
        row++;  // Move to the next row
    }

    if (player_count == 0)
        return (error("No player on the map"));
    
    return (0);
}

static t_map_node *add_map_node(t_map_node **head, char *line)
{
    t_map_node *new_node;
    t_map_node *temp;

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

static t_map_node *load_map(int fd)
{
    t_map_node *map_list = NULL;
    char *line;

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

char **get_map(t_map_node *map_list)
{
    int line_count = 0;
    t_map_node *temp = map_list;
    char **map;
    int i;

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
        int len = ft_strlen(map[i]);
        if (len > 0 && map[i][len - 1] == '\n')
            map[i][len - 1] = '\0';
        temp = temp->next;
        i++;
    }
    map[i] = NULL;

    return (map);
}

int init_map(t_game *game, char *path_user_input)
{
	int fd;
	t_map_node *map_list;

	if (ft_strncmp(".cub", path_user_input + ft_strlen(path_user_input) - 4, 4) != 0)
		return (error(ERROR_EXTENSION) );
	fd = gc_add_fd(open(path_user_input, O_RDONLY)); 
	if (fd < 0)
		return (error(ERROR_FD));
	map_list = load_map(fd);
	if (!map_list)
		return (error("Failed to load map"));
	if(check_map(map_list, &game->player) == 1)
		return (1);
	game->map = get_map(map_list);
	return (0);
}
