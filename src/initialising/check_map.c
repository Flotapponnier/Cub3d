#include "../../includes/cub3d.h"

static bool is_valid_map_char(char c)
{
    return (c == '1' || c == '0' || c == ' ' || c == '\n');
}

static bool is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	process_player(char c, int i, int row, t_player *player, int *player_count)
{
	(*player_count)++;
	if (*player_count > 1)
		return (error("More than one player on the map"));
	player->x = (i * 64) + 32;
	player->y = (row * 64) + 32;
	if (c == 'N')
		player->angle = 3 * PI / 2;
	else if (c == 'S')
		player->angle = PI / 2;
	else if (c == 'W')
		player->angle = PI;
	else if (c == 'E')
		player->angle = 0;
	return (0);
}

static int	validate_line(char *line, int row, t_player *player, int *player_count)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_valid_map_char(line[i]))
			i++;
		else if (is_player_char(line[i]))
		{
			if (process_player(line[i], i, row, player, player_count) != 0)
				return (-1);
			i++;
		}
		else
			return (error(ERROR_WRONG_CHAR));
	}
	return (0);
}

int	check_map(t_map_node *map_list, t_player *player)
{
	int			player_count;
	t_map_node	*temp;
	int			row;

	player_count = 0;
	temp = map_list;
	row = 0;
	while (temp)
	{
		if (validate_line(temp->line, row, player, &player_count) != 0)
			return (-1);
		temp = temp->next;
		row++;
	}
	if (player_count == 0)
		return (error("No player on the map"));
	return (0);
}
