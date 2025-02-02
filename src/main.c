/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:55 by ftapponn          #+#    #+#             */
/*   Updated: 2025/02/02 20:26:43 by dilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_game	game;

	atexit(leaks);
	if (argc != 2)
		return (error(ERROR_ARG), 1);
	init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
