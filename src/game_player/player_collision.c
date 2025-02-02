/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:29:00 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 11:30:14 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_wall(int x, int y, char **map)
{
	int	map_x1;
	int	map_y1;
	int	map_x2;
	int	map_y2;

	map_x1 = (x + SPACE_COLLISION) / BLOCK;
	map_y1 = (y + SPACE_COLLISION) / BLOCK;
	map_x2 = (x - SPACE_COLLISION) / BLOCK;
	map_y2 = (y - SPACE_COLLISION) / BLOCK;
	return (map[map_y1][map_x1] == '1' || map[map_y1][map_x2] == '1'
		|| map[map_y2][map_x1] == '1' || map[map_y2][map_x2] == '1');
}

static bool	check_single_point(float x, float y, char **map)
{
	int	map_x;
	int	map_y;

	map_x = x / BLOCK;
	map_y = y / BLOCK;
	return (map[map_y][map_x] == '1');
}

static t_pos	get_collision_point(float new_x, float new_y, float angle,
		float radius)
{
	t_pos	point;

	point.x = new_x + cos(angle) * radius;
	point.y = new_y + sin(angle) * radius;
	return (point);
}

static bool	check_collision(float new_x, float new_y, char **map)
{
	const int	num_points = 8;
	const float	radius = SPACE_COLLISION;
	float		angle;
	t_pos		check_point;
	int			i;

	i = 0;
	while (i < num_points)
	{
		angle = (2 * PI * i) / num_points;
		check_point = get_collision_point(new_x, new_y, angle, radius);
		if (check_single_point(check_point.x, check_point.y, map))
			return (true);
		i++;
	}
	return (false);
}

static void	update_position(t_player *player, float new_x, float new_y,
		char **map)
{
	if (check_collision(new_x, new_y, map))
	{
		if (!check_collision(new_x, player->y, map))
			player->x = new_x;
		else if (!check_collision(player->x, new_y, map))
			player->y = new_y;
	}
	else
	{
		player->x = new_x;
		player->y = new_y;
	}
}
