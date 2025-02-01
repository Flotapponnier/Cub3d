/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:49:52 by dilin             #+#    #+#             */
/*   Updated: 2025/02/01 19:50:41 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	normalize_tex_coords(float *tex_x, float *tex_y)
{
	*tex_x = fmod(*tex_x, 1.0);
	*tex_y = fmod(*tex_y, 1.0);
	if (*tex_x < 0)
		*tex_x += 1.0;
	if (*tex_y < 0)
		*tex_y += 1.0;
}

static void	get_pixel_coords(t_texture *tex, float tex_x, float tex_y,
		int *coords)
{
	coords[0] = (int)(tex_x * tex->width);
	coords[1] = (int)(tex_y * tex->height);
	if (coords[0] < 0)
		coords[0] = 0;
	else if (coords[0] >= tex->width)
		coords[0] = tex->width - 1;
	if (coords[1] < 0)
		coords[1] = 0;
	else if (coords[1] >= tex->height)
		coords[1] = tex->height - 1;
}

static uint32_t	convert_color(uint32_t color)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	a = (color >> 24) & 0xFF;
	b = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	r = color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_texture_color(t_texture *tex, float tex_x, float tex_y)
{
	int			coords[2];
	uint32_t	color;

	normalize_tex_coords(&tex_x, &tex_y);
	get_pixel_coords(tex, tex_x, tex_y, coords);
	color = tex->pixels[coords[1] * tex->width + coords[0]];
	return (convert_color(color));
}
