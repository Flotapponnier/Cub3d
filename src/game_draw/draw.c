/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/28 18:07:46 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool touch(float px, float py, t_game *game)
{
	int x;
	int y;

	x = px / BLOCK;
	y = py / BLOCK;
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

	while(!touch(ray_x, ray_y, game))
	{
		if(DEBUG)
			draw_raycast_line(game->img, (int)ray_x, (int)ray_y, RAYCAST_COLOR);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if(!DEBUG)
    	draw_wall_3d(game, i, ray_x, ray_y, player);
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
