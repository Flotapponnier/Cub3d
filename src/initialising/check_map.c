/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:15 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 09:14:31 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


static bool is_valid_map_char(char c)
{
    return (c == '1' || c == '0' || c == ' ' || c == '\n');
}

static bool is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int process_player(char c, int i, int row, t_player *player, int *player_count)
{
    (*player_count)++;
    if (*player_count > 1)
        return (error("More than one player on the map"));
    player->x = i;
    player->y = row;
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

static int validate_line(char *line, int row, t_player *player, int *player_count, int *map_width)
{
    int i = 0;
    int line_length = 0;

    while (line[i] != '\0')
    {
        if (is_valid_map_char(line[i]) || is_player_char(line[i]))
        {
            line_length = i + 1;
            if (is_player_char(line[i]) && process_player(line[i], i, row, player, player_count) != 0)
                return (-1);
        }
        else
            return (error(ERROR_WRONG_CHAR));
        i++;
    }

    if (*map_width == 0)
        *map_width = line_length;
    else if (line_length != *map_width)
        return (error("Inconsistent row widths in map"));

    return (0);
}


int check_map(t_map_node *map_list, t_player *player, t_game *game)
{
    int player_count;
    t_map_node *temp; 
    int row;
    int max_row_width;
	int current_row_width;

	temp = map_list;
	current_row_width = 0;
	row = 0;
	player_count = 0;
    while (temp)
    {
        current_row_width = strlen(temp->line);
        if (current_row_width > max_row_width)
            max_row_width = current_row_width;
        if (validate_line(temp->line, row, player, &player_count, &max_row_width) != 0)
            return (-1);
        temp = temp->next;
        row++;
    }
    if (player_count == 0)
        return (error("No player on the map"));
    game->map_struct.map_width = max_row_width;
    game->map_struct.map_height = row;
    printf("Map width: %d, Map height: %d\n", game->map_struct.map_width, game->map_struct.map_height);
    return (0);
}
