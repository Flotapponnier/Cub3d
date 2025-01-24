#include "../includes/cub3d.h"

void	destroy_cub3d(mlx_t *mlx, int status)
{
	if (mlx)
		mlx_terminate(mlx);
	gc_close_fds();
	gc_free();
	exit(status);
}
