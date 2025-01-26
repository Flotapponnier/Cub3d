/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:09 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/26 13:32:10 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_distance(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x;
	float delta_y;
	float angle;
	float fixed_distance;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fixed_distance = distance(delta_x, delta_y) * cos(angle);
	return (fixed_distance);
}

