/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_cub3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:32:00 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/03 20:13:44 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_cub3d(mlx_t *mlx, int status)
{
	if (mlx)
		mlx_terminate(mlx);
	gc_close_fds();
	gc_free();
	exit(status);
}
