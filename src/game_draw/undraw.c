/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:33:57 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/01 20:41:03 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_image(t_game *game)
{
	if (!game->img || !game->img->pixels)
		return ;
	ft_bzero(game->img->pixels, game->img->width * game->img->height
		* sizeof(int));
}
