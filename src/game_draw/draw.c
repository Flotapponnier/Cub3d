/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 17:02:08 by ftapponn         ###   ########.fr       */
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
		cast_ray(game, &game->ray, x);
		// Draw the wall slice with textures
		// Draw the ceiling slice
		if(!game->debug_view)
			draw_3d_monitor(game, x);
		wall_x = game->player.x + game->ray.ray_dir_x
			* game->ray.distance_to_wall * 64;
		wall_y = game->player.y + game->ray.ray_dir_y
			* game->ray.distance_to_wall * 64;
		ray_end_x = (int)wall_x;
		ray_end_y = (int)wall_y;
		if(game->debug_view)
		{
			draw_line(game->player.x, game->player.y, ray_end_x, ray_end_y, game,
			 RAYCAST_COLOR);
		}
		x++;
	}
	if(game->debug_view)
	{
		draw_square(game->player.x, game->player.y, SIZE_PLAYER, PLAYER_COLOR,
			  game);
		draw_map(game);
	}
}
