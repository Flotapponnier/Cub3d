/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:09 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 21:02:41 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_player *player, t_ray *ray, int x)
{
	double	fov_scale;

	fov_scale = tan(90 * M_PI / 360.0);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = cos(player->angle);
	ray->dir_y = sin(player->angle);
	ray->ray_dir_x = ray->dir_x + (-ray->dir_y) * fov_scale * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->dir_x * fov_scale * ray->camera_x;
	ray->map_x = (int)player->x / 64;
	ray->map_y = (int)player->y / 64;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	configure_ray(t_game *game, t_ray *ray)
{
	double	player_x;
	double	player_y;

	player_x = game->player.x / 64.0;
	player_y = game->player.y / 64.0;
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
		if (ray->map_x < 0 || ray->map_y < 0)
			break ;
		if (game->map[ray->map_y][ray->map_x] == '1')
			break ;
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
			ray->direction = 'E';
		else
			ray->direction = 'W';
	}
	else
	{
		ray->distance_to_wall = (ray->map_y - player_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
		if (ray->ray_dir_y > 0)
			ray->direction = 'S';
		else
			ray->direction = 'N';
	}
}

void	cast_ray(t_game *game, t_ray *ray, int x)
{
	init_ray(&game->player, &game->ray, x);
	configure_ray(game, ray);
	perform_dda(game, ray);
	calculate_wall_distance_and_direction(game, ray);
}
