/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:07:45 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 15:08:33 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_line_coordinates(t_line *line, t_line_coord *coord)
{
	line->x1 = coord->start_x;
	line->y1 = coord->start_y;
	line->x2 = coord->end_x;
	line->y2 = coord->end_y;
}

static void	init_line_direction(t_line *line)
{
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	line->sx = -1;
	line->sy = -1;
	if (line->x1 < line->x2)
		line->sx = 1;
	if (line->y1 < line->y2)
		line->sy = 1;
	line->err = line->dx - line->dy;
}

static void	draw_line_points(t_game *game, t_line *line, int color)
{
	while (1)
	{
		mlx_put_pixel(game->img, line->x1, line->y1, color);
		if (line->x1 == line->x2 && line->y1 == line->y2)
			break ;
		line->e2 = 2 * line->err;
		if (line->e2 > -line->dy)
		{
			line->err -= line->dy;
			line->x1 += line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err += line->dx;
			line->y1 += line->sy;
		}
	}
}

void	draw_line(int start_x, int start_y, t_line_params *params, t_game *game)
{
	t_line			line;
	t_line_coord	coord;

	coord.start_x = start_x;
	coord.start_y = start_y;
	coord.end_x = params->end_x;
	coord.end_y = params->end_y;
	init_line_coordinates(&line, &coord);
	init_line_direction(&line);
	draw_line_points(game, &line, params->color);
}
