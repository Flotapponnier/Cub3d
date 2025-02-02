/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilin <dilin@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:06:46 by dilin             #+#    #+#             */
/*   Updated: 2025/02/02 19:25:27 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_valid_rgb(int r, int g, int b)
{
	return (!(r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255));
}


uint32_t	convert_rgb_to_uint(char *color_str)
{
	char		**rgb;
	uint32_t	color;
	int			r;
	int			g;
	int			b;

	if (!color_str)
		return (0);
	rgb = gc_add_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		gc_free_ptr(rgb);
		return (0);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	gc_free_split(rgb);
	if (!is_valid_rgb(r, g, b))
		return (0);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (color);
}
