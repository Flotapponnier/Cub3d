/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:42 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 20:55:30 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	For debugging only. If needed, add to handle_key_press():
	if (keydata.key == MLX_KEY_B) 
		print_debug_info(game);
*/

/* void	print_debug_info(t_game *game)
{
	t_player	*player;
	int			grid_x;
	int			grid_y;
	int			rows;
	int			cols;
	float		angle_deg;
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
	int			y;
	int			x;

	player = &game->player;
	printf("===== DEBUG INFO =====\n");
	printf("Player Position: (%.2f, %.2f)\n", player->x, player->y);
	grid_x = (int)(player->x / BLOCK);
	grid_y = (int)(player->y / BLOCK);
	printf("Grid Position: (%d, %d)\n", grid_x, grid_y);
	rows = 0;
	while (game->map[rows] != NULL)
		rows++;
	if (grid_y >= 0 && grid_y < rows)
	{
		cols = ft_strlen(game->map[grid_y]);
		if (grid_x >= 0 && grid_x < cols)
			printf("Current Cell: %c\n", game->map[grid_y][grid_x]);
		else
			printf(
				"Current Cell: X out of bounds (GridX: %d, Map Columns: %d)\n",
				grid_x, cols);
	}
	else
		printf("Current Cell: Y out of bounds (GridY: %d, Map Rows: %d)\n",
			grid_y, rows);
	angle_deg = player->angle * (180.0 / PI);
	printf("Player Angle: %.2f radians (%.2f degrees)\n", player->angle,
		angle_deg);
	printf("Movement Keys:\n");
	if (player->key_up)
		printf("W (Up): Pressed\n");
	else
		printf("W (Up): Released\n");
	if (player->key_down)
		printf("S (Down): Pressed\n");
	else
		printf("S (Down): Released\n");
	if (player->key_left)
		printf("A (Left): Pressed\n");
	else
		printf("A (Left): Released\n");
	if (player->key_right)
		printf("D (Right): Pressed\n");
	else
		printf("D (Right): Released\n");
	if (player->left_rotate)
		printf("Left Rotate: Pressed\n");
	else
		printf("Left Rotate: Released\n");
	if (player->right_rotate)
		printf("Right Rotate: Pressed\n");
	else
		printf("Right Rotate: Released\n");
	rows = 0;
	while (game->map[rows] != NULL)
		rows++;
	printf("Map Dimensions: %d rows\n", rows);
	if (rows > 0)
	{
		cols = ft_strlen(game->map[0]);
		printf("First row length: %d columns\n", cols);
	}
	printf("\nNearby Map Cells (5x5 grid around player):\n");
	start_y = grid_y - 2;
	end_y = grid_y + 2;
	start_x = grid_x - 2;
	end_x = grid_x + 2;
	y = start_y;
	while (y <= end_y)
	{
		if (y < 0 || y >= rows)
		{
			printf("Row %d: Out of bounds\n", y);
			y++;
			continue ;
		}
		cols = ft_strlen(game->map[y]);
		printf("Row %2d: ", y);
		x = start_x;
		while (x <= end_x)
		{
			if (x < 0 || x >= cols)
				printf("  ");
			else
				printf("%c ", game->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("===== END DEBUG INFO =====\n\n");
} */

void	print_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
	{
		printf("Map is NULL\n");
		return ;
	}
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
