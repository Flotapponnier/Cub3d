/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/01/30 19:27:49 by dilin            ###   ########.fr       */
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
int	is_wall(int x, int y, char **map)
{
	int map_x1 = (x + SPACE_COLLISION) / BLOCK;
	int map_y1 = (y + SPACE_COLLISION) / BLOCK;
	int map_x2 = (x - SPACE_COLLISION) / BLOCK;
	int map_y2 = (y - SPACE_COLLISION) / BLOCK;

	return (map[map_y1][map_x1] == '1' ||
			map[map_y1][map_x2] == '1' ||
			map[map_y2][map_x1] == '1' ||
			map[map_y2][map_x2] == '1');
}

static bool check_collision(float new_x, float new_y, char **map)
{
    // Check a circle of points around the player
    const int num_points = 8;
    const float radius = SPACE_COLLISION;
    
    for (int i = 0; i < num_points; i++) {
        float angle = (2 * PI * i) / num_points;
        float check_x = new_x + cos(angle) * radius;
        float check_y = new_y + sin(angle) * radius;
        
        int map_x = check_x / BLOCK;
        int map_y = check_y / BLOCK;
        
        if (map[map_y][map_x] == '1')
            return true;
    }
    return false;
}

void handle_forward_backward(t_player *player, float cos_angle, 
    float sin_angle, int speed, char **map)
{
    float new_x, new_y;
    
    if (player->key_up)
    {
        new_x = player->x + cos_angle * speed;
        new_y = player->y + sin_angle * speed;
        
        if (check_collision(new_x, new_y, map)) {
            if (!check_collision(new_x, player->y, map))
                player->x = new_x;
            else if (!check_collision(player->x, new_y, map))
                player->y = new_y;
        }
        else {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->key_down)
    {
        new_x = player->x - cos_angle * speed;
        new_y = player->y - sin_angle * speed;
        
        if (check_collision(new_x, new_y, map)) {
            if (!check_collision(new_x, player->y, map))
                player->x = new_x;
            else if (!check_collision(player->x, new_y, map))
                player->y = new_y;
        }
        else {
            player->x = new_x;
            player->y = new_y;
        }
    }
}

void handle_strafing(t_player *player, float cos_angle, float sin_angle,
    int speed, char **map)
{
    float new_x, new_y;
    
    if (player->key_right)
    {
        new_x = player->x - sin_angle * speed;
        new_y = player->y + cos_angle * speed;
        
        if (check_collision(new_x, new_y, map)) {
            if (!check_collision(new_x, player->y, map))
                player->x = new_x;
            else if (!check_collision(player->x, new_y, map))
                player->y = new_y;
        }
        else {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (player->key_left)
    {
        new_x = player->x + sin_angle * speed;
        new_y = player->y - cos_angle * speed;
        
        if (check_collision(new_x, new_y, map)) {
            if (!check_collision(new_x, player->y, map))
                player->x = new_x;
            else if (!check_collision(player->x, new_y, map))
                player->y = new_y;
        }
        else {
            player->x = new_x;
            player->y = new_y;
        }
    }
}

void	move_player(t_player *player, char **map)
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
	handle_forward_backward(player, cos_angle, sin_angle, speed, map);
	handle_strafing(player, cos_angle, sin_angle, speed, map);
}
