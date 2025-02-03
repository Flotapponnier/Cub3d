/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:15 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/03 20:28:57 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void free_mapi(char **map)
{
    if (!map) // Check if the map pointer is NULL
        return;

    // Free each string in the array
    for (int i = 0; map[i]; i++)
    {
        free(map[i]); // Free the individual string
        map[i] = NULL; // Optional: Set the pointer to NULL to avoid dangling pointers
    }

    // Free the array of pointers itself
    free(map);
    map = NULL; // Optional: Set the pointer to NULL to avoid dangling pointers
}

static bool	process_pre_map_line(char *line, bool *map_started)
{
	if (!*map_started && ft_strlen(line) == 0)
		return (true);
	if (!*map_started && is_map_line(line))
	{
		*map_started = true;
		return (true);
	}
	return (false);
}

static int	validate_map_content(char **map, t_player *player, t_game *game)
{
	t_map_validator	ctx;
	bool			map_started;
	int				y;
	int				player_count;

	player_count = 0;
	map_started = false;
	y = 0;
	ctx = (t_map_validator){game, player, &player_count, map};
	while (map[y])
	{
		if (process_pre_map_line(map[y], &map_started))
		{
			y++;
			continue ;
		}
		if (map_started && ft_strlen(map[y]) == 0)
			return (error("Map contains empty lines within map content"));
		if (map_started && process_map_line(map[y], y, &ctx) != 0)
			return (1);
		y++;
	}
	if (player_count == 0)
		return (error("No player position found"));
	return (0);
}

static void	get_map_dimensions(char **map, t_game *game)
{
	int	i;
	int	len;

	game->map_struct.map_height = 0;
	game->map_struct.map_width = 0;
	while (map[game->map_struct.map_height])
		game->map_struct.map_height++;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > game->map_struct.map_width)
			game->map_struct.map_width = len;
		i++;
	}
}

static int	validate_and_store_map(char **map, t_player *player, t_game *game)
{
	if (validate_map_content(map, player, game) != 0)
	{
		gc_free_ptr(map);
		return (1);
	}
	free_mapi(map);
	return (0);
}

int	check_map(t_map_node *map_list, t_player *player, t_game *game)
{
	char	**map;

	if (!validate_map_textures_colors(&game->map_struct))
		return (error("Invalid textures or colors"));
	map = get_map(map_list);
	if (!map)
		return (error("Failed to process map"));
	get_map_dimensions(map, game);
	return (validate_and_store_map(map, player, game));
}
