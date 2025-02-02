/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:53 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/02 13:37:39 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

/* static int	get_texture_index(char direction)
{
	float		tex_x;
	float		step;
	float		tex_pos;
	float		end;
	uint32_t	color;
	int			tex_index;
	float		tex_x;
	int			j;

	if (direction == 'N')
		return (0);
	else if (direction == 'S')
		return (1);
	else if (direction == 'W')
		return (2);
	else if (direction == 'E')
		return (3);
	return (-1);
} */
/* static float	calculate_tex_x(float ray_x, float ray_y, char direction)
{
	if (direction == 'N' || direction == 'S')
		tex_x = fmod(ray_x, BLOCK) / BLOCK;
	else
		tex_x = fmod(ray_y, BLOCK) / BLOCK;
	if (direction == 'N' || direction == 'W')
		tex_x = 1.0f - tex_x;
	return (tex_x);
} */
/* static void	draw_wall_pixels(t_game *game, int i, t_texture *tex,
		float tex_x,
		float start_y, float wall_height)
{
	step = 1.0f / wall_height;
	tex_pos = 0;
	if (start_y < 0)
	{
		tex_pos = -start_y * step;
		start_y = 0;
	}
	end = start_y + wall_height;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (start_y < end)
	{
		color = get_texture_color(tex, tex_x, tex_pos);
		mlx_put_pixel(game->img, i, (int)start_y, color);
		tex_pos += step;
		start_y++;
	}
} */
/* void	draw_wall_slice(t_game *game, uint32_t i, float start_y,
		float wall_height, float ray_x, float ray_y, char direction)
{
	tex_index = get_texture_index(direction);
	if (tex_index == -1)
		return ;
	tex_x = calculate_tex_x(ray_x, ray_y, direction);
	draw_wall_pixels(game, i, &game->textures[tex_index], tex_x, start_y,
		wall_height);
} */

void	draw_floor_slice(t_game *game, int i, int start_y)
{
	int	j;

	j = start_y;
	while (j < HEIGHT)
	{
		mlx_put_pixel(game->img, i, j, game->floor_color);
		j++;
	}
}

void	draw_ceiling_slice(t_game *game, int i, int ceiling_end)
{
	int	j;

	j = 0;
	while (j < ceiling_end)
	{
		mlx_put_pixel(game->img, i, j, game->ceiling_color);
		j++;
	}
}

static void	draw_wall_texture(t_game *game, int x, t_texture *tex,
		t_draw_params *params)
{
	float		step;
	float		tex_pos;
	int			tex_y;
	uint32_t	color;
	int			y;

	step = 1.0 * tex->height / params->line_height;
	tex_pos = (params->draw_start - HEIGHT / 2 + params->line_height / 2)
		* step;
	y = params->draw_start;
	while (y < params->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		color = get_texture_color(tex, params->wall_x, (float)tex_y
				/ tex->height);
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_3d_monitor(t_game *game, int x)
{
	t_draw_params	params;

	params.perp_wall_dist = calculate_wall_distance(&game->ray, &game->player);
	calculate_draw_params(params.perp_wall_dist, &params.draw_start,
		&params.draw_end, &params.line_height);
	draw_ceiling_slice(game, x, params.draw_start);
	calculate_wall_texture(game, params.perp_wall_dist, &params.wall_x,
		&params.tex_num);
	draw_wall_texture(game, x, &game->textures[params.tex_num], &params);
	draw_floor_slice(game, x, params.draw_end);
}
