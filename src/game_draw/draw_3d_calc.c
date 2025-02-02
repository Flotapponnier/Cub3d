/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:37:22 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 17:48:40 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		return ((ray->map_x - player->x / 64.0 + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x);
	return ((ray->map_y - player->y / 64.0 + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y);
}

void	calculate_draw_params(double perp_wall_dist, int *draw_start,
		int *draw_end, int *line_height)
{
	double	correction;

	correction = 0.85;
	*line_height = (int)((HEIGHT * correction) / perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

void	calculate_wall_texture(t_game *game, double perp_wall_dist,
		double *wall_x, int *tex_num)
{
	if (game->ray.side == 0)
		*wall_x = game->player.y / 64.0 + perp_wall_dist * game->ray.ray_dir_y;
	else
		*wall_x = game->player.x / 64.0 + perp_wall_dist * game->ray.ray_dir_x;
	*wall_x -= floor(*wall_x);
	if (game->ray.direction == 'N')
		*tex_num = 0;
	else if (game->ray.direction == 'S')
		*tex_num = 1;
	else if (game->ray.direction == 'W')
		*tex_num = 2;
	else
		*tex_num = 3;
}
