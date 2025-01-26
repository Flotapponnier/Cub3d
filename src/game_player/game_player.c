/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/26 13:37:09 by ftapponn         ###   ########.fr       */
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
		float sin_angle, int speed)
{
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
}

void	handle_strafing(t_player *player, float cos_angle, float sin_angle,
		int speed)
{
	if (player->key_left)
	{
		player->x += -sin_angle * speed;
		player->y += cos_angle * speed;
	}
	if (player->key_right)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
}

void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = SPEED_PLAYER;
	angle_speed = ANGLE_SPEED;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	handle_rotation(player, angle_speed);
	handle_forward_backward(player, cos_angle, sin_angle, speed);
	handle_strafing(player, cos_angle, sin_angle, speed);
}
