/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/02 11:30:57 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handle_rotation(t_player *player, float angle_speed)
{
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	handle_forward_backward(t_player *player, float cos_angle,
		float sin_angle, char **map)
{
	if (player->key_up)
		handle_forward(player, cos_angle, sin_angle, map);
	if (player->key_down)
		handle_backward(player, cos_angle, sin_angle, map);
}

void	handle_strafing(t_player *player, float cos_angle, float sin_angle,
		char **map)
{
	t_angle	angle;

	angle.sin = sin_angle;
	angle.cos = cos_angle;
	if (player->key_right)
		handle_strafe_direction(player, angle, 1, map);
	if (player->key_left)
		handle_strafe_direction(player, angle, -1, map);
}

void	move_player(t_player *player, char **map)
{
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	angle_speed = ANGLE_SPEED;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_rotation(player, angle_speed);
	handle_forward_backward(player, cos_angle, sin_angle, map);
	handle_strafing(player, cos_angle, sin_angle, map);
}
