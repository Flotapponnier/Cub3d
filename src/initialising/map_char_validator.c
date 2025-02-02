/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_char_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 10:52:56 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 10:53:49 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static bool	is_map_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W')
			return (false);
		line++;
	}
	return (true);
}

static int	handle_map_char(char c, int x, int y, t_map_validator *ctx)
{
	if (!is_valid_map_char(c))
		return (error("Invalid character in map"));
	if (ft_strchr("NSEW", c))
	{
		if (!check_player_position(c, x, y, ctx))
			return (error("Invalid player position"));
	}
	else if (c == '0' && !check_surrounded_by_walls(ctx->map, x, y, ctx->game))
		return (error("Found hole in map walls"));
	return (0);
}

static int	process_map_line(char *line, int y, t_map_validator *ctx)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (handle_map_char(line[x], x, y, ctx) != 0)
			return (1);
		x++;
	}
	return (0);
}
