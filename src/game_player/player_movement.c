/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:29:06 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 11:30:38 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_forward(t_player *player, float cos_angle, float sin_angle,
		char **map)
{
	float	new_x;
	float	new_y;

	new_x = player->x + cos_angle * SPEED_PLAYER;
	new_y = player->y + sin_angle * SPEED_PLAYER;
	update_position(player, new_x, new_y, map);
}

static void	handle_backward(t_player *player, float cos_angle, float sin_angle,
		char **map)
{
	float	new_x;
	float	new_y;

	new_x = player->x - cos_angle * SPEED_PLAYER;
	new_y = player->y - sin_angle * SPEED_PLAYER;
	update_position(player, new_x, new_y, map);
}

static void	handle_strafe_direction(t_player *player, t_angle angle,
		int direction, char **map)
{
	float	new_x;
	float	new_y;

	if (direction == 1)
	{
		new_x = player->x - angle.sin * SPEED_PLAYER;
		new_y = player->y + angle.cos * SPEED_PLAYER;
	}
	else
	{
		new_x = player->x + angle.sin * SPEED_PLAYER;
		new_y = player->y - angle.cos * SPEED_PLAYER;
	}
	update_position(player, new_x, new_y, map);
}
