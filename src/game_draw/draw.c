/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 11:04:33 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

/*
static int	touch(float px, float py, t_game *game, int *side)
{
	int		x;
	int		y;
	float	frac_x;
	float	frac_y;
	float	edge;
	int		near_x_edge;
	int		near_y_edge;

    x = px / BLOCK;
    y = py / BLOCK;
    if (x < 0 || y < 0 || y >= game->map_struct.map_height
		|| x >= game->map_struct.map_width)
        return (1);
    if (game->map[y][x] == '1')
    {
        frac_x = (px / BLOCK) - x;
        frac_y = (py / BLOCK) - y;
        edge = 0.01f;
        near_x_edge = (frac_x < edge || frac_x > 1.0f - edge);
        near_y_edge = (frac_y < edge || frac_y > 1.0f - edge);
        if (near_x_edge && near_y_edge)
            *side = 3;
        else if (near_x_edge)
            *side = 1;
        else if (near_y_edge)
            *side = 2;
        else
            *side = 1;
        return (1);
    }
    return (0);
}

void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float		cos_angle;
	float		sin_angle;
	float		ray_x;
	float		ray_y;
	int			side;
	uint32_t	color;
	char		direction;
	float		dist;
	float		height;
	float		start_y;
	float		end;
	float		wall_height;

    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    ray_x = player->x;
    ray_y = player->y;
	side = 0;
	color = 0;
	while (1)
	{
		ray_x += cos_angle * 0.1;
		ray_y += sin_angle * 0.1;
		if (touch(ray_x, ray_y, game, &side))
			break ;
		if (game->debug_view)
			draw_raycast_line(game->img, (int)ray_x, (int)ray_y, RAYCAST_COLOR);
	}
	direction = 'l';
	if (side == 1)
	{
		if (cos_angle > 0)
		{
			direction = 'E';
			color = SQUARE3D_EAST;
		}
		else
	{
			direction = 'W';
			color = SQUARE3D_WEST;
		}
	}
	else if (side == 2)
	{
		if (sin_angle > 0)
		{
			direction = 'S';
			color = SQUARE3D_SOUTH;
		}
		else
		{
			direction = 'N';
			color = SQUARE3D_NORTH;
		}
	}
	else if (side == 3)
	{
		direction ='C';
		color = 0x0000FF;
	}
    printf("Wall hit: %c\n", direction);
    if (!game->debug_view)
    {
        dist = fixed_distance(player->x, player->y, ray_x, ray_y, game);
        height = (BLOCK / dist) * ((float)WIDTH / 2.0f);
        start_y = (HEIGHT - height) / 2.0f;
        end = start_y + height;
        if (dist <= 0) dist = 0.0001f;
        if (start_y < 0) start_y = 0;
        if (end >= HEIGHT) end = HEIGHT - 1;
        draw_floor_slice(game, i, start_y);
		draw_ceiling_slice(game, i, start_y);
        wall_height = end - start_y;
        draw_wall_slice(game, i, start_y, wall_height, ray_x, ray_y, direction);
    }
}

void	draw_loop(void *param)
{
	t_game		*game;
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

    game = (t_game *)param;
    player = &game->player;
	player = &game->player;
	move_player(player, game->map);
	clear_image(game);
	if (game->debug_view)
	{
		draw_square(player->x, player->y, SIZE_PLAYER, PLAYER_COLOR, game);
		draw_map(game);
	}
	fraction = FOV / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;	
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}
*/

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

void	cast_ray(t_game *game, t_ray *ray)
{
	configure_ray(game, ray);
	perform_dda(game, ray);
	calculate_wall_distance_and_direction(game, ray);
	printf("Wall hit: %c\n", ray->direction);
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

void	draw_line(int x1, int y1, int x2, int y2, t_game *game, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = -1;
	sy = -1;
	if (x1 < x2)
		sx = 1;
	if (y1 < y2)
		sy = 1;
	err = dx - dy;
	while (1)
	{
		mlx_put_pixel(game->img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

void	draw_loop(void *param)
{
	t_game		*game;
	t_player	*player;
	int			x;
	double		wall_x;
	double		wall_y;
	int			ray_end_x;
	int			ray_end_y;

	game = (t_game *)param;
	player = &game->player;
	move_player(player, game->map);
	clear_image(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&game->player, &game->ray, x);
		cast_ray(game, &game->ray);
		// Draw the wall slice with textures
		// Draw the ceiling slice
		draw_3d_monitor(game, x);
		wall_x = game->player.x + game->ray.ray_dir_x
			* game->ray.distance_to_wall * 64;
		wall_y = game->player.y + game->ray.ray_dir_y
			* game->ray.distance_to_wall * 64;
		ray_end_x = (int)wall_x;
		ray_end_y = (int)wall_y;
		draw_line(game->player.x, game->player.y, ray_end_x, ray_end_y, game,
				RAYCAST_COLOR);
		x++;
	}
	draw_square(game->player.x, game->player.y, SIZE_PLAYER, PLAYER_COLOR,
			game);
	draw_map(game);
}
