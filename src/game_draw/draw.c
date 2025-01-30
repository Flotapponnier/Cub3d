/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:47 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 20:30:48 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>



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
		if (DEBUG)
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
}
