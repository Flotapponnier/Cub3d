/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:54:00 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 18:24:53 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_player_direction(char c, t_player *player)
{
	if (c == 'N')
		player->angle = 3 * PI / 2;
	else if (c == 'S')
		player->angle = PI / 2;
	else if (c == 'W')
		player->angle = PI;
	else if (c == 'E')
		player->angle = 0;
}

bool	check_player_position(char c, int x, int y, t_map_validator *ctx)
{
	(*ctx->player_count)++;
	if (*(ctx->player_count) > 1)
		return (false);
	ctx->player->x = x;
	ctx->player->y = y;
	set_player_direction(c, ctx->player);
	return (check_surrounded_by_walls(ctx->map, x, y, ctx->game));
}

bool	check_surrounded_by_walls(char **map, int x, int y, t_game *game)
{
	if (x <= 0 || y <= 0 || x >= game->map_struct.map_width - 1
		|| y >= game->map_struct.map_height - 1)
		return (false);
	if (y - 1 < 0 || y + 1 >= game->map_struct.map_height || x - 1 < 0 || x
		+ 1 >= (int)ft_strlen(map[y]))
		return (false);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ')
		return (false);
	return (true);
}
