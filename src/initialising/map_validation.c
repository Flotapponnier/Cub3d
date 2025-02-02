/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:06:18 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 19:33:43 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_map_enclosed(t_game *game)
{
	int	result;

	result = flood_fill(game->map, game->map_struct.map_width,
			game->map_struct.map_height, (t_pos){game->player.x,
			game->player.y});
	if (result)
		return (error("Map is not enclosed!\n"));
	return (0);
}

int	process_map_data(t_game *game, t_map_node *map_list)
{
	if (check_map(map_list, &game->player, game) == 1)
		return (1);
	game->map = get_map(map_list);
	if (validate_map_enclosed(game))
		return (1);
	return (0);
}
