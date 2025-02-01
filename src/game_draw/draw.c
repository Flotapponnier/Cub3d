/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 08:13:26 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>


/*
static int touch(float px, float py, t_game *game, int *side)
{
    int x = px / BLOCK;
    int y = py / BLOCK;

    if (x < 0 || y < 0 || y >= game->map_struct.map_height || x >= game->map_struct.map_width)
        return (1);
    if (game->map[y][x] == '1')
    {
        float frac_x = (px / BLOCK) - x;
        float frac_y = (py / BLOCK) - y;
        float edge = 0.01f;
        int near_x_edge = (frac_x < edge || frac_x > 1.0f - edge);
        int near_y_edge = (frac_y < edge || frac_y > 1.0f - edge);

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

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;
	int side = 0;
	uint32_t color = 0;

	while (1)
	{
		ray_x += cos_angle * 0.1;
		ray_y += sin_angle * 0.1;
		if (touch(ray_x, ray_y, game, &side))
			break;
		if (game->debug_view)
			draw_raycast_line(game->img, (int)ray_x, (int)ray_y, RAYCAST_COLOR);
	}
	char direction = 'l';
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
        float dist = fixed_distance(player->x, player->y, ray_x, ray_y, game);
        float height = (BLOCK / dist) * ((float)WIDTH / 2.0f);
        float start_y = (HEIGHT - height) / 2.0f;
        float end = start_y + height;
        if (dist <= 0) dist = 0.0001f;
        if (start_y < 0) start_y = 0;
        if (end >= HEIGHT) end = HEIGHT - 1;
        draw_floor_slice(game, i, start_y);
		draw_ceiling_slice(game, i, start_y);
        float wall_height = end - start_y;
        draw_wall_slice(game, i, start_y, wall_height, ray_x, ray_y, direction);
    }
}

void draw_loop(void *param)
{
    t_game *game = (t_game *)param;
    t_player *player = &game->player;
	float fraction;
	float start_x;
	int i;

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
void cast_ray(t_game *game, t_ray *ray)
{
    // Convert player position to grid coordinates
    double player_x = game->player.x / 64.0;
    double player_y = game->player.y / 64.0;
    
    // Initialize step and side distances
    ray->step_x = (ray->ray_dir_x < 0) ? -1 : 1;
    ray->side_dist_x = (ray->ray_dir_x < 0) 
        ? (player_x - ray->map_x) * ray->delta_dist_x 
        : (ray->map_x + 1.0 - player_x) * ray->delta_dist_x;

    ray->step_y = (ray->ray_dir_y < 0) ? -1 : 1;
    ray->side_dist_y = (ray->ray_dir_y < 0)
        ? (player_y - ray->map_y) * ray->delta_dist_y
        : (ray->map_y + 1.0 - player_y) * ray->delta_dist_y;

    // DDA algorithm
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
            break;

        // Wall collision check (corrected map indexing)
		if (game->map[ray->map_y][ray->map_x] == '1')
        {
            // Calculate correct distance
            ray->distance_to_wall = (ray->side == 0)
                ? (ray->map_x - player_x + (1 - ray->step_x) / 2) / ray->ray_dir_x
                : (ray->map_y - player_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
            break;
        }
    }
}

void init_ray(t_player *player, t_ray *ray, int x)
{
    // Camera plane calculation (FOV)
    
    double fov_scale = tan(90 * M_PI / 360.0);  // 90° for half of 180° FOV
    ray->camera_x = 2 * x / (double)WIDTH - 1;  // X in camera space [-1, 1]
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
void draw_line(int x1, int y1, int x2, int y2, t_game *game, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;  // Direction of x
    int sy = (y1 < y2) ? 1 : -1;  // Direction of y
    int err = dx - dy;            // Error value

    while (1)
    {
        // Draw the pixel at (x1, y1)
        mlx_put_pixel(game->img, x1, y1, color);

        // Stop if we've reached the end point
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        // Adjust x-coordinate
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        // Adjust y-coordinate
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_loop(void *param)
{
    t_game *game = (t_game *)param;
	t_player *player = &game->player;

	move_player(player, game->map);
    clear_image(game);

    for (int x = 0; x < WIDTH; x++)
    {
	
        init_ray(&game->player, &game->ray, x);
        cast_ray(game, &game->ray);

        // Calculate endpoints with proper coordinate system
        double wall_x = game->player.x + game->ray.ray_dir_x * game->ray.distance_to_wall * 64;
        double wall_y = game->player.y + game->ray.ray_dir_y * game->ray.distance_to_wall * 64;
        
        // Convert to screen coordinates
        int ray_end_x = (int)wall_x;
        int ray_end_y = (int)wall_y;

        // Draw debug ray
            draw_line(game->player.x, game->player.y, 
                     ray_end_x, ray_end_y, game, RAYCAST_COLOR);
    }
    
    // Draw player and map in debug mode
        draw_square(game->player.x, game->player.y, SIZE_PLAYER, PLAYER_COLOR, game);
        draw_map(game);
}
