/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:09 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 11:28:05 by ftapponn         ###   ########.fr       */
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

void	init_ray(t_player *player, t_ray *ray, int x)
{
	double	fov_scale;

	// Camera plane calculation (FOV)
	fov_scale = tan(90 * M_PI / 360.0);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = cos(player->angle);
	ray->dir_y = sin(player->angle);
	// Calculate ray direction with FOV
	ray->ray_dir_x = ray->dir_x + (-ray->dir_y) * fov_scale * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->dir_x * fov_scale * ray->camera_x;
	// Initial map grid position
	ray->map_x = (int)player->x / 64;
	ray->map_y = (int)player->y / 64;
	// Calculate delta distances
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	configure_ray(t_game *game, t_ray *ray)
{
	double	player_x;
	double	player_y;

	// Convert player position to grid coordinates
	player_x = game->player.x / 64.0;
	player_y = game->player.y / 64.0;
	// Initialize step and side distances for X
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player_x) * ray->delta_dist_x;
	}
	// Initialize step and side distances for Y
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		// Boundary check
		if (ray->map_x < 0 || ray->map_y < 0)
			break ;
		// Wall collision check
		if (game->map[ray->map_y][ray->map_x] == '1')
		{
			break ;
		}
	}
}

void	calculate_wall_distance_and_direction(t_game *game, t_ray *ray)
{
	double	player_x;
	double	player_y;

	player_x = game->player.x / 64.0;
	player_y = game->player.y / 64.0;
	if (ray->side == 0)
	{
		ray->distance_to_wall = (ray->map_x - player_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
		if (ray->ray_dir_x > 0)
		{
			ray->direction = 'E';
		}
		else
		{
			ray->direction = 'W';
		}
	}
	else
	{
		ray->distance_to_wall = (ray->map_y - player_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
		if (ray->ray_dir_y > 0)
		{
			ray->direction = 'S';
		}
		else
		{
			ray->direction = 'N';
		}
	}
}

void	cast_ray(t_game *game, t_ray *ray, int x)
{

	init_ray(&game->player, &game->ray, x);
	configure_ray(game, ray);
	perform_dda(game, ray);
	calculate_wall_distance_and_direction(game, ray);
	printf("Wall hit: %c\n", ray->direction);
}


