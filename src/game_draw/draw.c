/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 09:33:18 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool touch(float px, float py, t_game *game)
{
	int x;
	int y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (x < 0 || y < 0 || y > game->map_struct.map_height || x > game->map_struct.map_width)
		return (true);
	if(game->map[y][x] == '1')
		return (true);
	return (false);
}


void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;

    while (!touch(ray_x, ray_y, game))
    {
		if (ray_x < 0 || ray_y < 0 || ray_x >= game->map_struct.map_width * BLOCK || ray_y >= game->map_struct.map_height * BLOCK)
            break;
        if (DEBUG)
            draw_raycast_line(game->img, (int)ray_x, (int)ray_y, RAYCAST_COLOR);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    if (!DEBUG)
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
        draw_wall_slice(game, i, start_y, end);
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
	if(DEBUG)
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
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
